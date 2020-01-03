// Copyright Ali El Saleh 2019

#include "BulletPatternSpawner.h"

#include "BulletPattern_Base.h"
#include "Bullet.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "ObjectPooler/ObjectPoolFunctionLibrary.h"
#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/StaticMesh.h"

ABulletPatternSpawner::ABulletPatternSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bCanBeDamaged = false;
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
	
	for (auto BulletPatternClass : BulletPatternClasses)
	{
		BulletPatterns.Add(NewObject<UBulletPattern_Base>(this, BulletPatternClass.Get(), BulletPatternClass->GetFName(), RF_NoFlags, BulletPatternClass.GetDefaultObject(), true));
	}

	if (ObjectPoolToUse)
	{
		ActiveBulletPool = UObjectPoolFunctionLibrary::GetObjectPool(this, ObjectPoolToUse.GetDefaultObject()->GetPoolName());
	}
	else
	{
		#if !UE_BUILD_SHIPPING
			check(ObjectPoolToUse && "Reference is null. Please make sure that the 'ObjectPoolToUse' property is not null.")
		#endif
	}

	ActiveBulletPattern = BulletPatterns[0];

#if !UE_BUILD_SHIPPING
	check(ActiveBulletPattern && "Reference is null. Please make sure that the 'Active Bullet Pattern' property is not null.")
#endif

	StartBulletPattern(ActiveBulletPattern);
}

void ABulletPatternSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (!bHasStarted)
		return;
	
	ActiveBulletPattern->EndPlay(EndPlayReason);
}

void ABulletPatternSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHasStarted)
		return;

	if (ElapsedTime > ActiveBulletPattern->GetFireRate())
	{
		ElapsedTime = 0.0f;

		ActiveBulletPattern->UpdatePattern(ActiveBulletPattern->GetFireRate());
		ActiveBulletPattern->UpdatePattern_BP(ActiveBulletPattern->GetFireRate());
	}

	ElapsedTime += DeltaTime;
	ActiveBulletPattern->Tick(DeltaTime);
	ActiveBulletPattern->Tick_BP(DeltaTime);
}

void ABulletPatternSpawner::SpawnBullet(UBulletPattern_Base* BulletPattern, const FVector& Direction, const float Speed)
{
	ABullet* Bullet = Cast<ABullet>(BulletPattern->GetBulletPool()->GetActorFromPool());

	Bullet->SetActorLocation(GetActorLocation());
	Bullet->SetupBehaviour(BulletPattern, Direction, Speed);

	Bullet->PooledActor_BeginPlay();
}

void ABulletPatternSpawner::StartBulletPattern(UBulletPattern_Base* BulletPattern)
{
	if (!BulletPattern)
		return;

	ActiveBulletPattern = BulletPattern;
	//RotatingMovementComponent->RotationRate = FRotator(0.0f, ActiveBulletPattern->GetSpinSpeed(), 0.0f);

	ActiveBulletPattern->AssignSpawner(this);
	ActiveBulletPattern->BeginPlay();
	ActiveBulletPattern->BeginPlay_BP();

	ResumeBulletPattern();
}

void ABulletPatternSpawner::ResumeBulletPattern()
{
	SetActorTickEnabled(true);
	ElapsedTime = 0.0f;

	bHasStarted = true;
}

void ABulletPatternSpawner::StopBulletPattern()
{
	SetActorTickEnabled(false);
	ElapsedTime = 0.0f;
	
	bHasStarted = false;
}

void ABulletPatternSpawner::ChangeBulletPattern(const TSubclassOf<UBulletPattern_Base> NewBulletPattern)
{
	StopBulletPattern();

	//ActiveBulletPattern->EndPlay(EEndPlayReason::Destroyed);

	StartBulletPattern(NewBulletPattern.GetDefaultObject());
}

void ABulletPatternSpawner::ChangeObjectPool(const TSubclassOf<UObjectPoolBase> NewObjectPool)
{
	if (NewObjectPool.GetDefaultObject())
	{
		ObjectPoolToUse = NewObjectPool;
		
		ActiveBulletPool = UObjectPoolFunctionLibrary::GetObjectPool(this, ObjectPoolToUse.GetDefaultObject()->GetPoolName());
	}
}
