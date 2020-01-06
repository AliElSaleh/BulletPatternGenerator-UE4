// Copyright Ali El Saleh 2019

#include "BulletPattern_Spiral.h"

#include "BulletPatternSpawner.h"

UBulletPattern_Spiral::UBulletPattern_Spiral()
{
	PatternName = "Spiral";
	FireRate = 0.1f;
	BulletSpeed = 500.0f;
}

void UBulletPattern_Spiral::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FQuat OldRotation = TargetRotation.Quaternion();
	const FQuat DeltaRotation = (RotationRate * DeltaTime).Quaternion();
	const FQuat NewRotation = (OldRotation * DeltaRotation);

	BulletPatternSpawner->SetActorRotation(NewRotation);
	TargetRotation = NewRotation.Rotator();
	BulletDirection = NewRotation.Vector().GetSafeNormal();
}
