// Copyright Ali El Saleh 2019


#include "BulletPattern_SineWaveBase.h"

#include "BulletPatternSpawner.h"

UBulletPattern_SineWaveBase::UBulletPattern_SineWaveBase()
{
	PatternName = "Sine Wave Pattern";
	BulletSpeed = 600.0f;
	SpinSpeed = 5.0f;
	FireRate = 0.1f;
}

void UBulletPattern_SineWaveBase::Tick(const float DeltaTime)
{
	ElapsedTime += DeltaTime * SpinSpeed;

	FRotator NewRotation = BulletPatternSpawner->GetActorRotation();
	const float DeltaRotationYaw = (FMath::Sin(ElapsedTime + DeltaTime) - FMath::Sin(ElapsedTime)) * AngleSpread.Yaw;
	const float DeltaRotationPitch = (FMath::Sin(ElapsedTime + DeltaTime) - FMath::Sin(ElapsedTime)) * AngleSpread.Pitch;
	const float DeltaRotationRoll = (FMath::Sin(ElapsedTime + DeltaTime) - FMath::Sin(ElapsedTime)) * AngleSpread.Roll;

	if (DeltaRotationYaw != 0.0f)
	{
		NewRotation.Yaw += DeltaRotationYaw;
	}

	if (DeltaRotationPitch != 0.0f)
	{
		NewRotation.Pitch += DeltaRotationPitch;
	}

	if (DeltaRotationRoll != 0.0f)
	{
		NewRotation.Roll += DeltaRotationRoll;
	}
	
	BulletPatternSpawner->SetActorRotation(NewRotation);
	BulletDirection = NewRotation.Vector().GetSafeNormal();

	ReceiveTick(DeltaTime);
}
