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
	if (PooledActors.Num() >= PoolSize)
		return;

	for (int32 i = 0; i < PoolSize; ++i)
	{
		AddActorToPool(SpawnPooledObject());
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

void UObjectPoolBase::AddActorToPool(APooledActor* NewPooledActor)
{
	NewPooledActor->AssignToPool(this);
	NewPooledActor->MarkNotInUse(false);

	// Place actor in the pool
	PooledActors.Add(NewPooledActor);
}

void UObjectPoolBase::RemoveActorFromPool(APooledActor* InPooledActor)
{
	PooledActors.Remove(InPooledActor);
}

APooledActor* UObjectPoolBase::GetActorFromPool()
{
	const auto RetrieveActor = [&]()
	{
		APooledActor* Null = nullptr; // Required for compliation to succeed

		for (auto Actor : PooledActors)
		{
			if (!Actor->IsInUse())
			{
				return Actor;
			}
		}

		return Null;
	};

	if (ReuseSetting == OPRS_Reuse)
	{
		if (AreAllActorsInUse())
		{
			for (auto Actor : PooledActors)
			{
				return Actor;
			}
		}

		return RetrieveActor();
	}

	if (ReuseSetting == OPRS_DoNotReuse)
	{
		return RetrieveActor();
	}

	if (ReuseSetting == OPRS_CreateNewActor)
	{
		if (AreAllActorsInUse())
		{
			APooledActor* SpawnedActor = SpawnPooledObject();
			AddActorToPool(SpawnedActor);
			
			return SpawnedActor;
		}

		return RetrieveActor();
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

bool UObjectPoolBase::AreAllActorsInUse() const
{
	int32 ActorsInUse = 0;
	for (auto Actor : PooledActors)
	{
		if (Actor->IsInUse())
			++ActorsInUse;
	}

	return ActorsInUse == PooledActors.Num();
}
