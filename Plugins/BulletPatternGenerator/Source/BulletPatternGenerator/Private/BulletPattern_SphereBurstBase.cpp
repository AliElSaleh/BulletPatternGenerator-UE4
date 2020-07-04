// Copyright Ali El Saleh 2019


#include "BulletPattern_SphereBurstBase.h"
#include "BulletPatternSpawner.h"
#include "BulletPatternFunctionLibrary.h"

#include "Async/ParallelFor.h"

UBulletPattern_SphereBurstBase::UBulletPattern_SphereBurstBase()
{
	PatternName = "Sphere Burst Base";
	FireRate = 2.0f;
	BulletSpeed = 600.0f;
}

void UBulletPattern_SphereBurstBase::BeginPlay()
{
	Super::BeginPlay();

	SetStartingRotation(BulletPatternSpawner->GetActorRotation());

	GenerateBulletDirections(NumOfWaysVertical, NumOfWaysHorizontal);
}

void UBulletPattern_SphereBurstBase::UpdatePattern(float DeltaTime)
{
	for (int32 i = 0; i < Directions.Num(); i++)
	{
		SpawnBulletInDirection(Directions[i]);
	}
}

void UBulletPattern_SphereBurstBase::GenerateBulletDirections(int32 InNumOfWaysVertical, int32 NumOfWaysHorizontal)
{
	Angle = MaxVerticalAngle/InNumOfWaysVertical;
	CurrentPhi = 0.0f;
	
	Directions.Empty();

	for (int32 i = 0; i < NumOfWaysHorizontal; i++)
	{
		for (int32 j = 0; j < InNumOfWaysVertical; j++)
		{
			FVector LocationOnSphere = UBulletPatternFunctionLibrary::CalculateLocationOnSphere(BulletPatternSpawner->GetActorLocation(), 1.0f, CurrentAngle, CurrentPhi);
			FVector NewBulletDirection = LocationOnSphere - BulletPatternSpawner->GetActorLocation();
			NewBulletDirection.Normalize();
			Directions.Add(NewBulletDirection);	

			CurrentAngle += Angle;
		}

		CurrentAngle = Angle;
		CurrentPhi += FMath::DegreesToRadians(MaxHorizontalAngle/(NumOfWaysHorizontal)/2);
	}
}
