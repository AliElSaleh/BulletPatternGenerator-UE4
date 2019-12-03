// Copyright Ali El Saleh 2019

#include "Bullet.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	SM_Bullet = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetStaticMesh(SM_Bullet);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->bApplyImpulseOnDamage = false;
	StaticMeshComponent->bReplicatePhysicsToAutonomousProxy = false;
	StaticMeshComponent->CanCharacterStepUpOn = ECB_No;

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletBeginOverlap);

	bCanBeDamaged = false;
	bFindCameraComponentWhenViewTarget = false;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		
}
