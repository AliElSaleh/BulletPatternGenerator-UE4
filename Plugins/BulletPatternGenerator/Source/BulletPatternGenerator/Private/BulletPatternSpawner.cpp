// Copyright Ali El Saleh 2019

#include "BulletPatternSpawner.h"

#include "BulletPattern_Base.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "Engine/StaticMesh.h"

ABulletPatternSpawner::ABulletPatternSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

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
	
	ActiveBulletPattern = BulletPatternClasses[0].GetDefaultObject();

	if (ActiveBulletPattern)
	{
		//PrimaryActorTick.TickInterval = ActiveBulletPattern->GetFireRate();
		ActiveBulletPattern->BeginPlay();
	}
}

void ABulletPatternSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (ActiveBulletPattern)
		ActiveBulletPattern->EndPlay(EndPlayReason);
}

void ABulletPatternSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (ActiveBulletPattern)
	{
		if (ElapsedTime > ActiveBulletPattern->GetFireRate())
		{
			ActiveBulletPattern->Tick(ActiveBulletPattern->GetFireRate());
			ElapsedTime = 0.0f;
		}
	}
}
