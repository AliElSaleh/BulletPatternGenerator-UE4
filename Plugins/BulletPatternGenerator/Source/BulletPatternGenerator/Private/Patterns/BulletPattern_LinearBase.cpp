// Copyright Ali El Saleh 2019


#include "BulletPattern_LinearBase.h"

#include "BulletPatternSpawner.h"

UBulletPattern_LinearBase::UBulletPattern_LinearBase()
{
	PatternName = "Linear";
	BulletSpeed = 500.0f;
	FireRate = 0.7f;
}

void UBulletPattern_LinearBase::UpdatePattern(float DeltaTime)
{
	SpawnBullet();
}
