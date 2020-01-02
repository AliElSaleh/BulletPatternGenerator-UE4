// Copyright Ali El Saleh 2019

#include "Bullet.h"

#include "Components/StaticMeshComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "BulletPatternBase.h"

#include "Engine/StaticMesh.h"

ABullet::ABullet()
	: APooledActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.SetTickFunctionEnable(false); 

	bEverAllowTick = false;
	bEverAllowCollisions = true;

	SM_Bullet = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetStaticMesh(SM_Bullet);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetCollisionProfileName("OverlapAll");
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComponent->SetCanEverAffectNavigation(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->bApplyImpulseOnDamage = false;
	StaticMeshComponent->bReplicatePhysicsToAutonomousProxy = false;
	StaticMeshComponent->CanCharacterStepUpOn = ECB_No;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->Velocity = FVector(0.0f);
	
	bCanBeDamaged = false;
	bFindCameraComponentWhenViewTarget = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
}

void ABullet::SetupBehaviour(class UBulletPattern_Base* BulletPattern, const FVector InDirection, const float InSpeed)
{
	//if (!BulletPattern)
	//	return;

	Direction = InDirection;
	Speed = InSpeed;
	
	ProjectileMovementComponent->Velocity = Direction * Speed;
}

void ABullet::OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, const int32 OtherBodyIndex, const bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(StaticClass()))
	{
		OnBulletHit.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		PooledActor_EndPlay();
	}
}
