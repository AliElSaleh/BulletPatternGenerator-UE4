// Copyright Ali El Saleh 2019

#include "BulletPatternSpawner.h"

#include "BulletPattern_Base.h"
#include "Bullet.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/StaticMesh.h"

ABulletPatternSpawner::ABulletPatternSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetCanBeDamaged(false);
	bFindCameraComponentWhenViewTarget = false;

	UStaticMesh* StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetStaticMesh(StaticMesh);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetCollisionProfileName("NoCollision");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetWorldScale3D(FVector(2.75f));
	StaticMeshComponent->CanCharacterStepUpOn = ECB_No;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bApplyImpulseOnDamage = false;
	StaticMeshComponent->bReplicatePhysicsToAutonomousProxy = false;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement Component"));
	RotatingMovementComponent->RotationRate = FRotator(0.0f);
}

void ABulletPatternSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (bDisableSpawner)
		Destroy();
	
	for (auto BulletPatternClass : BulletPatternClasses)
	{
		BulletPatterns.Add(NewObject<UBulletPattern_Base>(this, BulletPatternClass.Get(), BulletPatternClass->GetFName(), RF_NoFlags, BulletPatternClass.GetDefaultObject(), true));
	}

	// If we choose a pattern class from the editor, then use that
	if (BulletPatternClassFromEditor)
	{
		const int32 Index = BulletPatterns.Add(NewObject<UBulletPattern_Base>(this, BulletPatternClassFromEditor.Get(), BulletPatternClassFromEditor->GetFName(), RF_NoFlags, BulletPatternClassFromEditor.GetDefaultObject(), true));
		
		ActiveBulletPattern = BulletPatterns[Index];
	}
	else
	{
		ActiveBulletPattern = BulletPatterns[0];
	}

#if !UE_BUILD_SHIPPING
	check(ActiveBulletPattern && "Reference is null. Please make sure that the 'Active Bullet Pattern' property is not null.")
#endif

	StartBulletPattern(ActiveBulletPattern);
}

void ABulletPatternSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDisableSpawner)
		return;

	ActiveBulletPattern->CheckBulletsShouldDespawn();

	if (!bHasStarted)
		return;

	if (ElapsedTime > ActiveBulletPattern->GetFireRate())
	{
		ElapsedTime = 0.0f;

		ActiveBulletPattern->Broadcast_UpdatePattern_Event(ActiveBulletPattern->GetFireRate());
	}

	ElapsedTime += DeltaTime;
	ActiveBulletPattern->Broadcast_Tick_Event(DeltaTime);
}

void ABulletPatternSpawner::OnBulletPatternStarted_Implementation()
{
	if (ActiveBulletPattern)
		ActiveBulletPattern->SetStartingRotation(GetActorRotation());
}

void ABulletPatternSpawner::OnBulletPatternStopped_Implementation()
{
}

void ABulletPatternSpawner::OnBulletPatternChanged_Implementation()
{
}

ABullet* ABulletPatternSpawner::SpawnBullet(UBulletPattern_Base* BulletPattern, UObjectPoolBase* BulletPool, const FVector& Direction, const float Speed)
{
	ABullet* Bullet = Cast<ABullet>(BulletPool->GetActorFromPool());

	if (Bullet)
	{
		Bullet->SetActorLocation(GetActorLocation());
		Bullet->SetupBehaviour(BulletPattern, Direction, Speed);

		Bullet->PooledActor_BeginPlay();
	}

	return Bullet;
}

void ABulletPatternSpawner::StartBulletPattern(UBulletPattern_Base* BulletPattern)
{
	if (!BulletPattern)
		return;

	ActiveBulletPattern = BulletPattern;
	//RotatingMovementComponent->RotationRate = FRotator(0.0f, ActiveBulletPattern->GetSpinSpeed(), 0.0f);

	ActiveBulletPattern->AssignSpawner(this);
	ActiveBulletPattern->Initialize();
	ActiveBulletPattern->Broadcast_BeginPlay_Event();

	ResumeBulletPattern();

	OnBulletPatternStarted();
}

void ABulletPatternSpawner::ResumeBulletPattern()
{
	SetActorTickEnabled(true);
	ElapsedTime = 0.0f;

	bHasStarted = true;
}

void ABulletPatternSpawner::StopBulletPattern()
{
	//SetActorTickEnabled(false);
	ElapsedTime = 0.0f;
	
	bHasStarted = false;

	OnBulletPatternStopped();
}

void ABulletPatternSpawner::ChangeBulletPattern(const TSubclassOf<UBulletPattern_Base> NewBulletPattern)
{
	StopBulletPattern();

	StartBulletPattern(NewBulletPattern.GetDefaultObject());

	OnBulletPatternChanged();
}

FName ABulletPatternSpawner::GetActiveBulletPatternName() const
{
	return ActiveBulletPattern ? ActiveBulletPattern->GetPatternName() : "Null";
}
