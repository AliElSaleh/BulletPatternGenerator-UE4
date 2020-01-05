// Copyright Ali El Saleh 2019

#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"
#include "ObjectPooler/ObjectPoolManager.h"

#include "ObjectPooler/PooledActor.h"

TArray<class UObjectPoolBase*> UObjectPoolFunctionLibrary::ObjectPools;
TArray<class AObjectPoolManager*> UObjectPoolFunctionLibrary::ObjectPoolManagers;

AObjectPoolManager* UObjectPoolFunctionLibrary::GetObjectPoolManager(FName ManagerName)
{
	for (auto ObjectPoolManager : ObjectPoolManagers)
	{
		if (ObjectPoolManager->GetManagerName() == ManagerName)
			return ObjectPoolManager;
	}

	return nullptr;
}

TArray<AObjectPoolManager*> UObjectPoolFunctionLibrary::GetAllObjectPoolManagers()
{
	return ObjectPoolManagers;
}

UObjectPoolBase* UObjectPoolFunctionLibrary::GetObjectPool(const FName PoolName)
{
	for (auto ObjectPool : ObjectPools)
	{
		if (ObjectPool->GetPoolName() == PoolName)
			return ObjectPool;
	}

	return nullptr;
	
	//TArray<AActor*> FoundObjectPools;
	//UGameplayStatics::GetAllActorsOfClass(WorldContextObject, UObjectPoolBase::StaticClass(), FoundObjectPools);
	//
	//for (auto FoundObjectPool : FoundObjectPools)
	//{
	//	const auto ObjectPool = Cast<UObjectPoolBase>(FoundObjectPool);
	//	
	//	if (ObjectPool->GetPoolName() == PoolName)
	//		return ObjectPool;
	//}
	//
	//return nullptr;
}

TArray<UObjectPoolBase*> UObjectPoolFunctionLibrary::GetAllObjectPools()
{
	return ObjectPools;
	//TArray<AActor*> FoundActors;
	//TArray<UObjectPoolBase*> FoundObjectPools;
	//UGameplayStatics::GetAllActorsOfClass(WorldContextObject, UObjectPoolBase::StaticClass(), FoundActors);
	//
	//for (auto FoundActor : FoundActors)
	//{
	//	const auto ObjectPool = Cast<UObjectPoolBase>(FoundActor);
	//	FoundObjectPools.Add(ObjectPool);
	//}
	//
	//return FoundObjectPools;
}

void UObjectPoolFunctionLibrary::MarkActorNotInUse(APooledActor* InPooledActor)
{
	InPooledActor->MarkNotInUse();
}

void UObjectPoolFunctionLibrary::MarkActorInUse(APooledActor* InPooledActor)
{
	InPooledActor->MarkInUse();
}

bool UObjectPoolFunctionLibrary::IsActorInUse(APooledActor* InPooledActor)
{
	return InPooledActor ? InPooledActor->IsInUse() : false;
}