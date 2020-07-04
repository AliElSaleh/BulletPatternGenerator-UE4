// Copyright Ali El Saleh 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncRetrieveActorFromPool_Comp.generated.h"

/**
 * An async function task to retrieve an actor that's not in use from an object pool component
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UAsyncRetrieveActorFromPool_Comp : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
    /**
    * Schedule an async task to retrieve an actor from the given object pool
    *
    * @param InObjectPoolComponent			The object pool component to use to retrieve an actor that's not in use.
    */
    UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Category = "SaveGame",  WorldContext = "WorldContextObject"), DisplayName = "Async Retrieve Actor From Pool (Component)")
    static UAsyncRetrieveActorFromPool_Comp* AsyncRetrieveActorFromPool_Component(UObject* WorldContextObject, class UObjectPoolComponent* InObjectPoolComponent);

	/** Delegate called when actor retrieval completes */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAsyncHandleRetrieveActor, class UObjectPoolComponent*, ObjectPool, class APooledActor*, RetrievedActor, bool, bSuccess);
	UPROPERTY(BlueprintAssignable)
    FOnAsyncHandleRetrieveActor Completed;

	/** Execute the actual operation */
	virtual void Activate() override;

protected:
    UPROPERTY()
    UObjectPoolComponent* ObjectPoolComponent;

	UPROPERTY()
    APooledActor* RetrievedActor;
	
	/** Function callbacks for actor retrieval */
	void HandleAsyncRetrieveActor();
	
	/** Called at completion of actor retrieval to execute delegate */
	void ExecuteCompleted(bool bSuccess);
};
