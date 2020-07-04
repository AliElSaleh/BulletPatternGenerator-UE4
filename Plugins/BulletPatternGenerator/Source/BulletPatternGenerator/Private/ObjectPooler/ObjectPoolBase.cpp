// Copyright Ali El Saleh 2020

#include "ObjectPoolBase.h"
#include "ObjectPoolFunctionLibrary.h"
#include "PooledActor.h"

#include "Engine/World.h"

UObjectPoolBase::UObjectPoolBase()
{
}

void UObjectPoolBase::BeginPlay()
{
	if (bFillPoolOnBeginPlay)
		FillPool();
}

void UObjectPoolBase::Tick(const float DeltaTime)
{
	if (WarmUp.bEnabled && WarmUp.WarmUpCounter < WarmUp.WarmUpAcross && PoolChunks.Num() > 0)
	{
		for (int32 i = 0 ; i < PoolChunks[WarmUp.WarmUpCounter].Num(); i++)
		{
			AddActorToPool(SpawnPooledObject());
		}
	
		WarmUp.WarmUpCounter++;
		
		if (WarmUp.WarmUpCounter == WarmUp.WarmUpAcross)
			WarmUp.bWarmUpComplete = true;
	}
}

void UObjectPoolBase::FillPool()
{
	World = GetWorld();

	if (PooledActors.Num() >= PoolSize || WarmUp.bWarmUpComplete)
		return;

	if (WarmUp.bEnabled && WarmUp.WarmUpAcross > 1 && WarmUp.WarmUpAcross <= PoolSize)
	{
		WarmUp.WarmUpCounter = 0;
		WarmUp.bWarmUpComplete = false;
		
		PoolChunks = UObjectPoolFunctionLibrary::SplitPoolSize(PoolSize, WarmUp.WarmUpAcross);
	}
	else
	{
		WarmUp.bEnabled = false;

		for (int32 i = 0; i < PoolSize; ++i)
		{
			AddActorToPool(SpawnPooledObject());
		}
		
		WarmUp.bWarmUpComplete = true;
	}
}

void UObjectPoolBase::EmptyPool()
{
	PooledActors.Empty();
}

APooledActor* UObjectPoolBase::SpawnPooledObject()
{
	return World->SpawnActor<APooledActor>(ObjectClassToPool, FVector(0.0f), FRotator(0.0f));
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

APooledActor* UObjectPoolBase::GetActorFromPool(EObjectPoolRetrieveActorResult& Results)
{
	if (!WarmUp.bWarmUpComplete)
	{
		Results = EObjectPoolRetrieveActorResult::Failed;
		return nullptr;
	}
	
	const auto RetrieveActor = [&]()
    {
	    APooledActor* NullActor = nullptr;
		
	    for (APooledActor* Actor : PooledActors)
	    {
		    if (Actor && Actor->IsNotInUse())
		    {
			    Results = EObjectPoolRetrieveActorResult::Succeeded;
			    return Actor;
		    }
		}

	    Results = EObjectPoolRetrieveActorResult::Failed;
	    return NullActor;
    };

    if (ReuseSetting == EObjectPoolReuseSetting::Reuse)
    {
	    if (AreAllActorsInUse())
	    {
		    Results = EObjectPoolRetrieveActorResult::Succeeded;
		    return PooledActors[0];
		}

		return RetrieveActor();
    }

    if (ReuseSetting == EObjectPoolReuseSetting::DoNotReuse)
    {
		return RetrieveActor();
    }

    if (ReuseSetting == EObjectPoolReuseSetting::CreateNewActor)
    {
	    if (AreAllActorsInUse())
	    {
		    APooledActor* SpawnedActor = SpawnPooledObject();
		    AddActorToPool(SpawnedActor);

		    Results = EObjectPoolRetrieveActorResult::Succeeded;
		    return SpawnedActor;
		}

		return RetrieveActor();
    }

    return RetrieveActor();
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
		if (Actor && Actor->IsInUse())
			++ActorsInUse;
	}

	return PooledActors.Num() != 0 && ActorsInUse == PooledActors.Num();
}
