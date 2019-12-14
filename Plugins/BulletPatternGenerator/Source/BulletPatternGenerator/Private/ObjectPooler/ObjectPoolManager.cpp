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
		SpawnObjectPool(ObjectPool.Value);
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
		if (ObjectPool.Key == InPoolName)
			return ObjectPool.Value.GetDefaultObject();
	}

	return nullptr;
}

FString AObjectPoolManager::GetPoolName(AObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.Value.GetDefaultObject() == InObjectPool)
			return ObjectPool.Key;
	}

	return FString("Null");
}

TSubclassOf<AObjectPoolBase> AObjectPoolManager::GetPoolClass(AObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.Value.GetDefaultObject() == InObjectPool)
			return ObjectPool.Value->GetClass();
	}

	return nullptr;
}

TSubclassOf<AObjectPoolBase> AObjectPoolManager::GetPoolClassFromString(const FString InPoolName)
{
	for (auto ObjectPool : ObjectPools)
	{
		if (ObjectPool.Key == InPoolName)
			return ObjectPool.Value->GetClass();
	}

	return nullptr;
}
