// Copyright Ali El Saleh 2020

#include "ObjectPooler/AsyncRetrieveActorFromPool_Comp.h"

#include "ObjectPooler/ObjectPoolComponent.h"

UAsyncRetrieveActorFromPool_Comp* UAsyncRetrieveActorFromPool_Comp::AsyncRetrieveActorFromPool_Component( UObject* WorldContextObject, UObjectPoolComponent* InObjectPoolComponent)
{
	UAsyncRetrieveActorFromPool_Comp* Action = NewObject<UAsyncRetrieveActorFromPool_Comp>();
	Action->ObjectPoolComponent = InObjectPoolComponent;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void UAsyncRetrieveActorFromPool_Comp::Activate()
{
	if (ObjectPoolComponent)
	{
		HandleAsyncRetrieveActor();
		return;
	}

	UE_LOG(LogScript, Error, TEXT("UAsyncTaskRetrieveActorFromPool Created with invalid operation!"));

	ExecuteCompleted(false);
}

void UAsyncRetrieveActorFromPool_Comp::HandleAsyncRetrieveActor()
{
	AsyncTask(ENamedThreads::GameThread, [&]()
    {
        if (ObjectPoolComponent)
        {
            EObjectPoolRetrieveActorResult Result;	
            RetrievedActor = ObjectPoolComponent->GetActorFromPool(Result);
            ExecuteCompleted(RetrievedActor != nullptr);
        }
    });
}

void UAsyncRetrieveActorFromPool_Comp::ExecuteCompleted(const bool bSuccess)
{
	Completed.Broadcast(ObjectPoolComponent, RetrievedActor, bSuccess);

	ObjectPoolComponent = nullptr;
	SetReadyToDestroy();
}
