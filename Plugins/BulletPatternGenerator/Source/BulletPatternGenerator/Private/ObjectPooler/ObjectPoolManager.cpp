// Copyright Ali El Saleh 2019

#include "ObjectPoolManager.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "ObjectPoolFunctionLibrary.h"

AObjectPoolManager::AObjectPoolManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.SetTickFunctionEnable(false); 

	bFindCameraComponentWhenViewTarget = false;
	bCanBeDamaged = false;
}

void AObjectPoolManager::PostInitializeComponents()
{	
	Super::PostInitializeComponents();

	if (UObjectPoolFunctionLibrary::ObjectPools.Num() > 0)
		DestroyAllObjectPools();

	SpawnAllObjectPools();

	for (auto ObjectPool : UObjectPoolFunctionLibrary::ObjectPools)
	{
		ObjectPool->BeginPlay();
	}
}

void AObjectPoolManager::SpawnAllObjectPools()
{
	for (const auto ObjectPool : ObjectPools)
	{
		SpawnObjectPool(ObjectPool);
	}
}

void AObjectPoolManager::DestroyAllObjectPools()
{
	UObjectPoolFunctionLibrary::ObjectPools.Empty();
}

void AObjectPoolManager::SpawnObjectPool(const TSubclassOf<UObjectPoolBase> InPoolClass)
{
	//check(InPoolClass && "A crash occured because a pool class is null. Check the ObjectPoolManager actor in the world and make sure that there are no empty properties in the object pool array.");

	if (InPoolClass)
		UObjectPoolFunctionLibrary::ObjectPools.Add(NewObject<UObjectPoolBase>(this, InPoolClass.Get(), InPoolClass->GetFName(), RF_NoFlags, InPoolClass.GetDefaultObject(), true));
}

UObjectPoolBase* AObjectPoolManager::GetPool(const FString InPoolName)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool.GetDefaultObject();
	}

	return nullptr;
}

FString AObjectPoolManager::GetPoolName(UObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool.GetDefaultObject()->GetPoolName().ToString();
	}

	return FString("Null");
}

TSubclassOf<UObjectPoolBase> AObjectPoolManager::GetPoolClass(UObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool;
	}

	return nullptr;
}

TSubclassOf<UObjectPoolBase> AObjectPoolManager::GetPoolClassFromString(const FString InPoolName)
{
	for (auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool;
	}

	return nullptr;
}
