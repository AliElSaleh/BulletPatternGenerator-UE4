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

	StartingRotation = (LockOnTarget->GetActorLocation() - BulletPatternSpawner->GetActorLocation()).Rotation();
	//StartingRotation = UKismetMathLibrary::FindLookAtRotation(BulletPatternSpawner->GetActorLocation(), LockOnTarget->GetActorLocation()) + AngleSpread*0.5f;
	BulletPatternSpawner->SetActorRotation(StartingRotation);
}

void UBulletPattern_SineWaveLockOn::Tick(const float DeltaTime)
{
	StartingRotation = (LockOnTarget->GetActorLocation() - BulletPatternSpawner->GetActorLocation()).Rotation();

	BulletPatternSpawner->SetActorRotation(StartingRotation);

	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void UBulletPattern_SineWaveLockOn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == "bLogActorList")
	{
		bLogActorList = false;
		
		LogActorListToConsole();
	}
}

void UBulletPattern_SineWaveLockOn::LogActorListToConsole()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *GetName(), *Actor->GetName())
	}
}
#endif
