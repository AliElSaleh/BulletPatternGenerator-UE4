// Copyright Ali El Saleh 2019

#include "ObjectPoolBase.h"

#include "PooledActor.h"

#include "Engine/World.h"

UObjectPoolBase::UObjectPoolBase()
{
}

void UObjectPoolBase::BeginPlay()
{
	World = GetWorld();

	FillPool();
}

void UObjectPoolBase::FillPool()
{
	for (int32 i = 0; i < PoolSize; ++i)
	{
		APooledActor* SpawnedActor = SpawnPooledObject();

		SpawnedActor->AssignToPool(this);
		SpawnedActor->MarkNotInUse();
		
		// Place actor in the pool
		PooledActors.Add(SpawnedActor);
	}
}

APooledActor* UObjectPoolBase::SpawnPooledObject()
{
	return World->SpawnActor<APooledActor>(ObjectClassToPool, CurrentLocation, CurrentRotation);
}

void UObjectPoolBase::EmptyPool()
{
	PooledActors.Empty();
}

void UObjectPoolBase::RemoveActorFromPool(APooledActor* InPooledActor)
{
	PooledActors.Remove(InPooledActor);
}

APooledActor* UObjectPoolBase::GetActorFromPool()
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

FName UObjectPoolBase::GetPoolName() const
{
	return PoolName;
}

int32 UObjectPoolBase::GetPoolSize() const
{
	return PoolSize;
}
