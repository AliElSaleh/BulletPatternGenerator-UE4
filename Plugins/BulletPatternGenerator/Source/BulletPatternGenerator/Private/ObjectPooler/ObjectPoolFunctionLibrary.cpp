// Copyright Ali El Saleh 2019

#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Kismet/GameplayStatics.h"

AObjectPoolBase* UObjectPoolFunctionLibrary::GetObjectPool(const UObject* WorldContextObject, const FName PoolName)
{
	TArray<AActor*> FoundObjectPools;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AObjectPoolBase::StaticClass(), FoundObjectPools);

	for (auto FoundObjectPool : FoundObjectPools)
	{
		const auto ObjectPool = Cast<AObjectPoolBase>(FoundObjectPool);
		
		if (ObjectPool->GetPoolName() == PoolName)
			return ObjectPool;
	}

	return nullptr;
}

TArray<AObjectPoolBase*> UObjectPoolFunctionLibrary::GetAllObjectPools(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	TArray<AObjectPoolBase*> FoundObjectPools;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AObjectPoolBase::StaticClass(), FoundActors);

	for (auto FoundActor : FoundActors)
	{
		const auto ObjectPool = Cast<AObjectPoolBase>(FoundActor);
		FoundObjectPools.Add(ObjectPool);
	}

	return FoundObjectPools;
}
