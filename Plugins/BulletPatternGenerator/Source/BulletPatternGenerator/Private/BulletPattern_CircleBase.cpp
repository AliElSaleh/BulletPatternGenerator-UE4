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

	
}

FVector2D UBulletPattern_CircleBase::CalculatePositionOnCircle(const FVector2D Origin, const float Radius, const float Angle)
{
	return FVector2D(Origin.X + Radius * FMath::Cos(FMath::DegreesToRadians(Angle)), Origin.Y + Radius * FMath::Sin(FMath::DegreesToRadians(Angle)));
}

FVector UBulletPattern_CircleBase::CalculateLocationOnSphere(const FVector Origin, const float Radius, const float Angle, const float Phi)
{
	const float X = Origin.X + Radius * FMath::Sin(FMath::DegreesToRadians(Angle)) * FMath::Cos(Phi);
	const float Y = Origin.Y + Radius * FMath::Sin(FMath::DegreesToRadians(Angle)) * FMath::Sin(Phi);
	const float Z = Origin.Z + Radius * FMath::Cos(FMath::DegreesToRadians(Angle));

	return FVector(X, Y, Z);
}
