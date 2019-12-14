// Copyright Ali El Saleh 2019

#include "ObjectPoolFunctionLibrary.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Kismet/GameplayStatics.h"


AObjectPoolBase* UObjectPoolFunctionLibrary::GetObjectPool(const UObject* WorldContextObject, const FName PoolName)
{
	TArray<AActor*> FoundObjectPools;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AObjectPoolBase::StaticClass(), FoundObjectPools);

	for (auto ObjectPool : FoundObjectPools)
	{
		const auto NewObjectPool = Cast<AObjectPoolBase>(ObjectPool);
		
		if (NewObjectPool->GetPoolName() == PoolName)
			return NewObjectPool;
	}

	return nullptr;
}
