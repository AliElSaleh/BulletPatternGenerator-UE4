// Copyright Ali El Saleh 2019


#include "BulletPattern_LinearLockOn.h"

#include "BulletPatternSpawner.h"

#include "GameFramework/Pawn.h"

UBulletPattern_LinearLockOn::UBulletPattern_LinearLockOn()
{
	PatternName = "Linear Lock-On";
	BulletSpeed = 700.0f;
	FireRate = 0.7f;
}

void UBulletPattern_LinearLockOn::BeginPlay()
{
	Super::BeginPlay();

	BulletDirection = (Player->GetActorLocation() - BulletPatternSpawner->GetActorLocation()).GetSafeNormal();
}

void UBulletPattern_LinearLockOn::UpdatePattern(const float DeltaTime)
{
	BulletDirection = (Player->GetActorLocation() - BulletPatternSpawner->GetActorLocation()).GetSafeNormal();
	
	Super::UpdatePattern(DeltaTime);
}
