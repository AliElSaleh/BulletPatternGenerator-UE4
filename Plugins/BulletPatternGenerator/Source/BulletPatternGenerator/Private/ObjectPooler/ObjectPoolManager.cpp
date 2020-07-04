// Copyright Ali El Saleh 2020

#include "ObjectPoolManager.h"
#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"

AObjectPoolManager::AObjectPoolManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.SetTickFunctionEnable(true); 

	bFindCameraComponentWhenViewTarget = false;
	SetCanBeDamaged(false);
}

void AObjectPoolManager::BeginPlay()
{
	Super::BeginPlay();

}

void AObjectPoolManager::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UObjectPoolBase*> ObjectPools = UObjectPoolFunctionLibrary::GetAllObjectPools();
	for (UObjectPoolBase* ObjectPool : ObjectPools)
	{
		if (ObjectPool)
			ObjectPool->Tick(DeltaTime);
	}
}

void AObjectPoolManager::PostInitializeComponents()
{	
	Super::PostInitializeComponents();

	SpawnAllObjectPools();
}

void AObjectPoolManager::SpawnAllObjectPools()
{
	for (const auto ObjectPoolClass : ObjectPoolClasses)
	{
		SpawnObjectPool(ObjectPoolClass);
	}
}

void AObjectPoolManager::SpawnObjectPool(const TSubclassOf<UObjectPoolBase> InPoolClass)
{
	if (InPoolClass)
	{
		UObjectPoolBase* ObjectPool = NewObject<UObjectPoolBase>(this, InPoolClass.Get(), InPoolClass->GetFName(), RF_NoFlags, InPoolClass.GetDefaultObject(), true);
		if (ObjectPool)
		{
			ObjectPool->BeginPlay();
		}
	}
}

UObjectPoolBase* AObjectPoolManager::GetPool(const FString InPoolName)
{
	for (const auto ObjectPool : ObjectPoolClasses)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool.GetDefaultObject();
	}

	return nullptr;
}

FString AObjectPoolManager::GetPoolName(UObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPoolClasses)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool.GetDefaultObject()->GetPoolName().ToString();
	}

	return FString("Null");
}

TSubclassOf<UObjectPoolBase> AObjectPoolManager::GetPoolClass(UObjectPoolBase* InObjectPool)
{
	for (const auto ObjectPool : ObjectPoolClasses)
	{
		if (ObjectPool.GetDefaultObject() == InObjectPool)
			return ObjectPool;
	}

	return nullptr;
}

TSubclassOf<UObjectPoolBase> AObjectPoolManager::GetPoolClassFromString(const FString InPoolName)
{
	for (auto ObjectPool : ObjectPoolClasses)
	{
		if (ObjectPool.GetDefaultObject()->GetPoolName().ToString() == InPoolName)
			return ObjectPool;
	}

	return nullptr;
}
