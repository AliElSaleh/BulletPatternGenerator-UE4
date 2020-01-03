// Copyright Ali El Saleh 2019

#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"
#include "ObjectPooler/ObjectPoolManager.h"

#include "ObjectPooler/PooledActor.h"

#include "Kismet/GameplayStatics.h"

TArray<class UObjectPoolBase*> UObjectPoolFunctionLibrary::ObjectPools;
TArray<class AObjectPoolManager*> UObjectPoolFunctionLibrary::ObjectPoolManagers;

AObjectPoolManager* UObjectPoolFunctionLibrary::GetObjectPoolManager(const UObject* WorldContextObject, FName ManagerName)
{
	for (auto ObjectPoolManager : ObjectPoolManagers)
	{
		if (ObjectPoolManager->GetManagerName() == ManagerName)
			return ObjectPoolManager;
	}

	return nullptr;
}

TArray<AObjectPoolManager*> UObjectPoolFunctionLibrary::GetAllObjectPoolManagers(const UObject* WorldContextObject)
{
	return ObjectPoolManagers;
}

UObjectPoolBase* UObjectPoolFunctionLibrary::GetObjectPool(const UObject* WorldContextObject, const FName PoolName)
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

TArray<UObjectPoolBase*> UObjectPoolFunctionLibrary::GetAllObjectPools(const UObject* WorldContextObject)
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