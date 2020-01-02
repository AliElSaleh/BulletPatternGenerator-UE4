// Copyright Ali El Saleh 2019

#include "ObjectPoolBase.h"

#include "PooledActor.h"

#include "Engine/World.h"

AObjectPoolBase::AObjectPoolBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer = false;

	bBlockInput = true;

	bCanBeDamaged = false;
	bFindCameraComponentWhenViewTarget = false;
}

void AObjectPoolBase::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	CurrentLocation = GetActorLocation();
	CurrentRotation = GetActorRotation();

	// Fill up the pool
	for (int32 i = 0; i < PoolSize; ++i)
	{
		APooledActor* SpawnedActor = SpawnPooledObject();

		SpawnedActor->AssignToPool(this);
		SpawnedActor->MarkNotInUse();
		
		// Place actor in the pool
		PooledActors.Add(SpawnedActor);
	}
}

APooledActor* AObjectPoolBase::GetActorFromPool()
{
	for (auto Actor : PooledActors)
	{
		if (!Actor->IsInUse())
		{
			return Actor;
		}
	}
	
	return nullptr;
}

void AObjectPoolBase::RemoveActorFromPool(APooledActor* InPooledActor)
{
	PooledActors.Remove(InPooledActor);
}

FName AObjectPoolBase::GetPoolName() const
{
	return PoolName;
}

int32 AObjectPoolBase::GetPoolSize() const
{
	return PoolSize;
}

APooledActor* AObjectPoolBase::SpawnPooledObject()
{
	return World->SpawnActor<APooledActor>(ObjectClassToPool, CurrentLocation, CurrentRotation);
}
