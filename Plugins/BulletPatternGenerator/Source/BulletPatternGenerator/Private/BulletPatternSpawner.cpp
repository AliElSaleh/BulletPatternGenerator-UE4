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
	
	if (ObjectPoolToUse)
	{
		ActiveBulletPool = UObjectPoolFunctionLibrary::GetObjectPool(this, ObjectPoolToUse.GetDefaultObject()->GetPoolName());
	}
	else
	{
		TArray<AObjectPoolBase*> ObjectPools = UObjectPoolFunctionLibrary::GetAllObjectPools(this);

		if (ObjectPools.Num() > 0 && ObjectPools[0])
			ActiveBulletPool = ObjectPools[0];
	}

	ActiveBulletPattern = ActiveBulletPatternClass.GetDefaultObject();

#if !UE_BUILD_SHIPPING
	check(ActiveBulletPattern && "Reference is null. Please make sure that the 'Active Bullet Pattern' property is not null.")
#endif

	ActiveBulletPattern->BeginPlay();

	StartBulletPattern(ActiveBulletPattern);
}

void ABulletPatternSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ActiveBulletPattern->EndPlay(EndPlayReason);
}

void ABulletPatternSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (ElapsedTime > ActiveBulletPattern->GetFireRate())
	{
		ActiveBulletPattern->Tick(ActiveBulletPattern->GetFireRate());
		SpawnBullet();
		ElapsedTime = 0.0f;
	}
}

void ABulletPatternSpawner::SpawnBullet()
{
	ABullet* Bullet = Cast<ABullet>(ActiveBulletPool->GetActorFromPool());
	Bullet->SetActorLocation(GetActorLocation());
	Bullet->SetupBehaviour(ActiveBulletPattern, GetActorForwardVector(), ActiveBulletPattern->GetBulletSpeed());

	Bullet->PooledActor_BeginPlay();
}

void ABulletPatternSpawner::StartBulletPattern(UBulletPattern_Base* BulletPattern)
{
	if (!BulletPattern)
		return;
	
	ActiveBulletPattern = BulletPattern;
	RotatingMovementComponent->RotationRate = FRotator(0.0f, ActiveBulletPattern->GetSpinSpeed(), 0.0f);

	ElapsedTime = 0.0f;
	SetActorTickEnabled(true);
}

void ABulletPatternSpawner::StopBulletPattern()
{
	SetActorTickEnabled(false);
	ElapsedTime = 0.0f;
}

void ABulletPatternSpawner::ChangeBulletPattern(const TSubclassOf<UBulletPattern_Base> NewBulletPattern)
{
	StopBulletPattern();

	ActiveBulletPattern = NewBulletPattern.GetDefaultObject();

	StartBulletPattern(ActiveBulletPattern);
}

void ABulletPatternSpawner::ChangeObjectPool(const TSubclassOf<AObjectPoolBase> NewObjectPool)
{
	if (NewObjectPool.GetDefaultObject())
	{
		ObjectPoolToUse = NewObjectPool;
		
		ActiveBulletPool = UObjectPoolFunctionLibrary::GetObjectPool(this, ObjectPoolToUse.GetDefaultObject()->GetPoolName());
	}
}
