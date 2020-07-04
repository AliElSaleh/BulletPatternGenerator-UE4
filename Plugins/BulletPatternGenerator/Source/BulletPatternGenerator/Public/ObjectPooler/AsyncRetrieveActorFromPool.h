// Copyright Ali El Saleh 2020

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncRetrieveActorFromPool.generated.h"

/**
 * An async function task to retrieve an actor that's not in use from an object pool
 */
UCLASS(BlueprintType)
class BULLETPATTERNGENERATOR_API UAsyncRetrieveActorFromPool final : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	/**
	 * Schedule an async task to retrieve an actor from the given object pool
	 *
	 * @param InObjectPool			The object pool to use to retrieve an actor that's not in use.
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Category = "SaveGame",  WorldContext = "WorldContextObject"))
	static UAsyncRetrieveActorFromPool* AsyncRetrieveActorFromPool(UObject* WorldContextObject, class UObjectPoolBase* InObjectPool);

	/** Delegate called when actor retrieval completes */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAsyncHandleRetrieveActor, class UObjectPoolBase*, ObjectPool, class APooledActor*, RetrievedActor, bool, bSuccess);
	UPROPERTY(BlueprintAssignable)
	FOnAsyncHandleRetrieveActor Completed;

	/** Execute the actual operation */
	virtual void Activate() override;

protected:
	UPROPERTY()
    UObjectPoolBase* ObjectPool;

	UPROPERTY()
	APooledActor* RetrievedActor;
	
	/** Function callbacks for actor retrieval */
	void HandleAsyncRetrieveActor();
	
	/** Called at completion of actor retrieval to execute delegate */
	void ExecuteCompleted(bool bSuccess);
};
