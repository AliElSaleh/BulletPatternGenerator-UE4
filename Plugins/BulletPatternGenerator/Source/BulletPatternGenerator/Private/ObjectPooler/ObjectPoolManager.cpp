// Copyright Ali El Saleh 2019

#include "ObjectPoolManager.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/World.h"

AObjectPoolManager::AObjectPoolManager()
{
	bFindCameraComponentWhenViewTarget = false;
}

void AObjectPoolManager::BeginPlay()
{
	World = GetWorld();

	Location = GetActorLocation();
	Rotation = GetActorRotation();
	
	SpawnAllObjectPools();
}

void AObjectPoolManager::SpawnAllObjectPools()
{
	for (const auto ObjectPool : ObjectPools)
	{
		SpawnObjectPool(ObjectPool);
	}
}

void AObjectPoolManager::SpawnObjectPool(const TSubclassOf<AObjectPoolBase> InPoolClass) const
{
	check(InPoolClass);

	World->SpawnActor(InPoolClass, &Location, &Rotation);
}

AObjectPoolBase* AObjectPoolManager::GetPool(const FString InPoolName)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool.GetDefaultObject();
	}

	return nullptr;
}

FString AObjectPoolManager::GetPoolName(AObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool.GetDefaultObject()->GetPoolName().ToString();
	}

	return FString("Null");
}

TSubclassOf<AObjectPoolBase> AObjectPoolManager::GetPoolClass(AObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool;
	}

	return nullptr;
}

TSubclassOf<AObjectPoolBase> AObjectPoolManager::GetPoolClassFromString(const FString InPoolName)
{
	for (auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool;
	}

	return nullptr;
}
