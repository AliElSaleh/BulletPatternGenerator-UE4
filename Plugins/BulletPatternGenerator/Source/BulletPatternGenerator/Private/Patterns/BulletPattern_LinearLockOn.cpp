// Copyright Ali El Saleh 2019


#include "BulletPattern_LinearLockOn.h"

#include "BulletPatternSpawner.h"

#include "GameFramework/Actor.h"

#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"

UBulletPattern_LinearLockOn::UBulletPattern_LinearLockOn()
{
	PatternName = "Linear Lock-On";
	BulletSpeed = 700.0f;
	FireRate = 0.7f;
}

void UBulletPattern_LinearLockOn::BeginPlay()
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
}

void UBulletPattern_LinearLockOn::UpdatePattern(const float DeltaTime)
{
	if (LockOnTarget)
	{
		BulletDirection = LockOnTarget->GetActorLocation() - BulletPatternSpawner->GetActorLocation();
		
		Super::UpdatePattern(DeltaTime);
	}
}

#if WITH_EDITOR
void UBulletPattern_LinearLockOn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == "bLogActorList")
	{
		bLogActorList = false;
		
		LogActorListToConsole();
	}
}

void UBulletPattern_LinearLockOn::LogActorListToConsole()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GWorld, AActor::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *GetName(), *Actor->GetName())
	}
}
#endif
