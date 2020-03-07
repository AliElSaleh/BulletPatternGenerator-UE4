// Copyright Ali El Saleh 2019

#include "BulletPattern_CircleBase.h"

UBulletPattern_CircleBase::UBulletPattern_CircleBase()
{
	PatternName = "Circle";
	FireRate = 0.1f;
	BulletSpeed = 700.0f;
}

void UBulletPattern_CircleBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	//const FQuat OldRotation = TargetRotation.Quaternion();
	//const FQuat DeltaRotation = (RotationRate * DeltaTime).Quaternion();
	//const FQuat NewRotation = (OldRotation * DeltaRotation);

	////BulletPatternSpawner->SetActorRotation(NewRotation);
	//TargetRotation = NewRotation.Rotator();
	//BulletDirection = NewRotation.Vector().GetSafeNormal();
}
