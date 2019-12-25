// Copyright Ali El Saleh 2019

#include "Bullet.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SM_Bullet = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetStaticMesh(SM_Bullet);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionProfileName("OverlapAll");
	StaticMeshComponent->SetCanEverAffectNavigation(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->bApplyImpulseOnDamage = false;
	StaticMeshComponent->bReplicatePhysicsToAutonomousProxy = false;
	StaticMeshComponent->CanCharacterStepUpOn = ECB_No;

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	bCanBeDamaged = false;
	bFindCameraComponentWhenViewTarget = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(MaxLifetime);
}

void ABullet::Destroyed()
{
	OnBulletDestroyed.Broadcast();
	OnDestroyed();
}

void ABullet::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OnBulletHit.Broadcast(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ABullet::OnDestroyed_Implementation()
{
	OnBulletDestroyed.Broadcast();
}
