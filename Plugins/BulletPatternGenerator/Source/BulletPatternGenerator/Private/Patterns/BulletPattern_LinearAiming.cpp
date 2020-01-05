// Copyright Ali El Saleh 2019


#include "BulletPattern_LinearAiming.h"

#include "BulletPatternSpawner.h"

#include "GameFramework/Pawn.h"

UBulletPattern_LinearAiming::UBulletPattern_LinearAiming()
{
	PatternName = "Linear Aiming";
	BulletSpeed = 1000.0f;
	FireRate = 0.1f;
}

void UBulletPattern_LinearAiming::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	BulletDirection = (Player->GetActorLocation() - BulletPatternSpawner->GetActorLocation()).GetSafeNormal();
}
