// Copyright Ali El Saleh 2020

#include "ObjectPooler/ObjectPoolComponent.h"
#include "ObjectPoolFunctionLibrary.h"
#include "ObjectPooler/PooledActor.h"

UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;	
}

void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bFillPoolOnBeginPlay)
		FillPool();
}

void UObjectPoolComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UObjectPoolComponent::FillPool()
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

void UObjectPoolComponent::EmptyPool()
{
	PooledActors.Empty();
}

APooledActor* UObjectPoolComponent::SpawnPooledObject()
{
	return World->SpawnActor<APooledActor>(ObjectClassToPool, FVector(0.0f), FRotator(0.0f));
}

void UObjectPoolComponent::AddActorToPool(APooledActor* NewPooledActor)
{
	NewPooledActor->MarkNotInUse(false);

	// Place actor in the pool
	PooledActors.Add(NewPooledActor);
}

void UObjectPoolComponent::RemoveActorFromPool(APooledActor* InPooledActor)
{
	PooledActors.Remove(InPooledActor);
}

APooledActor* UObjectPoolComponent::GetActorFromPool(EObjectPoolRetrieveActorResult& Results)
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

FName UObjectPoolComponent::GetPoolName() const
{
	return PoolName;
}

int32 UObjectPoolComponent::GetPoolSize() const
{
	return PoolSize;
}

bool UObjectPoolComponent::AreAllActorsInUse() const
{
	int32 ActorsInUse = 0;
	for (auto Actor : PooledActors)
	{
		if (Actor && Actor->IsInUse())
			++ActorsInUse;
	}

	return ActorsInUse == PooledActors.Num();
}
