// Copyright Ali El Saleh 2019


#include "BulletPattern_SpinnableBase.h"

UBulletPattern_SpinnableBase::UBulletPattern_SpinnableBase()
{
	PatternName = "Spinnable";
	BulletSpeed = 500.0f;
	FireRate = 0.1f;
}

void UBulletPattern_SpinnableBase::UpdatePattern(float DeltaTime)
{
	SpawnBullet();
}
