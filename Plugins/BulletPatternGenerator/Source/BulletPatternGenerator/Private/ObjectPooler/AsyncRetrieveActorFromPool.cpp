// Copyright Ali El Saleh 2020

#include "ObjectPooler/AsyncRetrieveActorFromPool.h"
#include "ObjectPooler/ObjectPoolBase.h"

UAsyncRetrieveActorFromPool* UAsyncRetrieveActorFromPool::AsyncRetrieveActorFromPool(UObject* WorldContextObject, UObjectPoolBase* InObjectPool)
{
	UAsyncRetrieveActorFromPool* Action = NewObject<UAsyncRetrieveActorFromPool>();
	Action->ObjectPool = InObjectPool;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void UAsyncRetrieveActorFromPool::Activate()
{
	if (ObjectPool)
	{
		HandleAsyncRetrieveActor();
		return;
	}

	UE_LOG(LogScript, Error, TEXT("UAsyncTaskRetrieveActorFromPool Created with invalid operation!"));

	ExecuteCompleted(false);
}

void UAsyncRetrieveActorFromPool::HandleAsyncRetrieveActor()
{
	AsyncTask(ENamedThreads::GameThread, [&]()
	{
		if (ObjectPool)
		{
			EObjectPoolRetrieveActorResult Result;	
			RetrievedActor = ObjectPool->GetActorFromPool(Result);
			ExecuteCompleted(RetrievedActor != nullptr);
		}
	});
}

void UAsyncRetrieveActorFromPool::ExecuteCompleted(const bool bSuccess)
{
	Completed.Broadcast(ObjectPool, RetrievedActor, bSuccess);

	ObjectPool = nullptr;
	SetReadyToDestroy();
}
