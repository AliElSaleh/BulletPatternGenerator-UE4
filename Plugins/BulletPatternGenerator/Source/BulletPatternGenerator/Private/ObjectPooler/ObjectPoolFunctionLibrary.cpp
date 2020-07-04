// Copyright Ali El Saleh 2020

#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"
#include "ObjectPooler/ObjectPoolManager.h"

#include "ObjectPooler/PooledActor.h"

AObjectPoolManager* UObjectPoolFunctionLibrary::GetObjectPoolManager(const FName ManagerName)
{
	TArray<AObjectPoolManager*> ObjectPoolManagers = GetAllObjectsOfClass<AObjectPoolManager>();
	
	for (auto ObjectPoolManager : ObjectPoolManagers)
	{
		if (ObjectPoolManager && ObjectPoolManager->GetManagerName() == ManagerName)
			return ObjectPoolManager;
	}

	return nullptr;
}

TArray<AObjectPoolManager*> UObjectPoolFunctionLibrary::GetAllObjectPoolManagers()
{
	return GetAllObjectsOfClass<AObjectPoolManager>();
}

UObjectPoolBase* UObjectPoolFunctionLibrary::GetObjectPool(const FName PoolName)
{
	TArray<UObjectPoolBase*> ObjectPools = GetAllObjectsOfClass<UObjectPoolBase>();

	for (UObjectPoolBase* ObjectPool : ObjectPools)
	{
		if (ObjectPool && ObjectPool->GetPoolName() == PoolName)
			return ObjectPool;
	}

	return nullptr;
}

TArray<UObjectPoolBase*> UObjectPoolFunctionLibrary::GetAllObjectPools()
{
	return GetAllObjectsOfClass<UObjectPoolBase>();
}

bool UObjectPoolFunctionLibrary::DoesObjectPoolExist(const FName PoolName)
{
	TArray<UObjectPoolBase*> ObjectPools = GetAllObjectsOfClass<UObjectPoolBase>();

	for (UObjectPoolBase* ObjectPool : ObjectPools)
	{
		if (ObjectPool && ObjectPool->GetPoolName() == PoolName)
			return true;
	}

	return false;
}

int32 UObjectPoolFunctionLibrary::GetNumOfObjectPoolsInWorld()
{
	return GetAllObjectPools().Num();
}

void UObjectPoolFunctionLibrary::DestroyAllObjectPools()
{
	TArray<UObjectPoolBase*> ObjectPools = GetAllObjectsOfClass<UObjectPoolBase>();

	for (UObjectPoolBase* ObjectPool : ObjectPools)
	{
		if (ObjectPool)
			ObjectPool->BeginDestroy();
	}

	ObjectPools.Empty();
}

void UObjectPoolFunctionLibrary::MarkActorNotInUse(APooledActor* InPooledActor)
{
	if (InPooledActor)
		InPooledActor->MarkNotInUse();
}

void UObjectPoolFunctionLibrary::MarkActorInUse(APooledActor* InPooledActor)
{
	if (InPooledActor)
		InPooledActor->MarkInUse();
}

bool UObjectPoolFunctionLibrary::IsActorInUse(APooledActor* InPooledActor)
{
	return InPooledActor ? InPooledActor->IsInUse() : false;
}

TArray<TArray<int32>> UObjectPoolFunctionLibrary::SplitPoolSize(const int32 PoolSize, const int32 InChunks)
{
	if (InChunks <= 1)
		return TArray<TArray<int32>>();
	
	const int32 ElementsPerChunk = PoolSize/InChunks;
	const int32 LeftOverElements = PoolSize%InChunks;

	TArray<TArray<int32>> Chunks;
	Chunks.Reserve(InChunks);
	
	TArray<int32> ElementsToAdd;
	ElementsToAdd.Reserve(ElementsPerChunk);
	
	for (int32 i = 0; i < InChunks; i++)
	{
		for (int32 j = i*ElementsPerChunk; j < ElementsPerChunk*(i+1); j++)
		{
			ElementsToAdd.Add(j);
		}

		Chunks.Add(ElementsToAdd);
		ElementsToAdd.Empty(ElementsPerChunk);
	}

	ElementsToAdd.Empty(ElementsPerChunk);

	for (int32 i = PoolSize-LeftOverElements; i < PoolSize; i++)
	{
		ElementsToAdd.Add(i);
	}

	if (ElementsToAdd.Num() > 0)
		Chunks.Add(ElementsToAdd);

	return Chunks;
}
