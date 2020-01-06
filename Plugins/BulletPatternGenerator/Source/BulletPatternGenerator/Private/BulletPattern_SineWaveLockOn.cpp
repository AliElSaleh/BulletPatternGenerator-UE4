// Copyright Ali El Saleh 2019


#include "BulletPattern_SineWaveLockOn.h"

#include "GameFramework/Actor.h"

#include "BulletPatternSpawner.h"

#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBulletPattern_SineWaveLockOn::UBulletPattern_SineWaveLockOn()
{
	PatternName = "Sine Wave Lock-On";
	FireRate = 0.1f;
	SpinSpeed = 5.0f;
	BulletSpeed = 600.0f;
}

void UBulletPattern_SineWaveLockOn::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AActor::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		if (bLogActorList)
			UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *GetName(), *Actor->GetName())

		if (Actor->GetName() == LockOnActorName)
		{
			LockOnTarget = Actor;
			break;
		}
	}

	if (LockOnTarget)
	{
		BulletDirection = LockOnTarget->GetActorLocation() - BulletPatternSpawner->GetActorLocation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: LockOnTarget is null. Failed to find actor '%s' in %s. Please make sure that 'LockOnActorName' is correct!"), *GetName(), *LockOnActorName, *GetWorld()->GetMapName())
	}

	TargetRotation = UKismetMathLibrary::FindLookAtRotation(BulletPatternSpawner->GetActorLocation(), LockOnTarget->GetActorLocation()) + AngleSpread*0.5f;
}
