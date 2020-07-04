// Copyright Ali El Saleh 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolerEnums.h"
#include "ObjectPoolerStructs.h"
#include "ObjectPoolComponent.generated.h"

UCLASS(ClassGroup=("Object Pool"), meta=(BlueprintSpawnableComponent))
class BULLETPATTERNGENERATOR_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPoolComponent();

	/**
	 * Retrieves an actor from the pool that's not currently in use. If all actors in the pool are in use, a null reference will be returned.
	 *
	 * @return An actor reference from the pool. Null if there are no actors in the pool
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool", meta = (ExpandEnumAsExecs = "Results"))
	virtual class APooledActor* GetActorFromPool(EObjectPoolRetrieveActorResult& Results);
	
	/**
	 * Removes an actor from the pool. ONLY USE SPARINGLY. Call 'PooledActor_EndPlay' from the pooled actor to return it to the pool.
	 * Alternatively, call 'MarkActorNotInUse' from an object pool.
	 *
	 * @param InPooledActor	 The pooled actor to remove from the pool
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void RemoveActorFromPool(class APooledActor* InPooledActor);

	/**
	 * Retrieves the name of the pool
	 *
	 * @returns				The pool's name
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	FName GetPoolName() const;

	/**
	 * Retrieves the size of the pool
	 *
	 * @returns				The pool's size
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	int32 GetPoolSize() const;

	/**
	 * Checks to see if all the actors in the pool are in use.
	 *
	 * @returns				True, if all actors in the pool are in use. Otherwise, false
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	bool AreAllActorsInUse() const;
	
	/**
	 * Is the pool empty? (i.e Are there no actors in the pool?)
	 *
	 * @returns				True, if there are no actors in the pool. Otherwise, false
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	FORCEINLINE bool IsPoolEmpty() const { return PooledActors.Num() == 0; }

	/**
	* If warm up is enabled, has the warm up process finished?
	*
	* @returns				True, if warm up has been completed. Otherwise, false
	*/
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	FORCEINLINE bool IsWarmUpComplete() const { return WarmUp.bEnabled ? WarmUp.bWarmUpComplete : true; }

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/**
	 * Spawns an actor from the pool into the world. Marks the actor not in use as well
	 *
	 * @return A newly created pooled actor
	 */
	virtual class APooledActor* SpawnPooledObject();

	/**
	 * Fills up the pool with actors, specified by the PoolSize (Spawns actors and adds them to the pool)
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void FillPool();

	/**
	 * Empties the pool (Destroying all actors in the pool)
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void EmptyPool();

	/**
	 * Adds an actor to the pool
	 *
	 * @param NewPooledActor	 The pooled actor to add to the pool
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void AddActorToPool(class APooledActor* NewPooledActor);

	// The name of the pool
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings")
	FName PoolName = "Default";

	// The amount of objects that are allowed in the pool. 200,000 is the maximum that each pool can support
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings", meta = (UIMin = 1, ClampMin = 0, UIMax = 200000))
	int32 PoolSize = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings")
	EObjectPoolReuseSetting ReuseSetting = EObjectPoolReuseSetting::Reuse;

	// The actor class to pool
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings", DisplayName = "Object to Pool")
	TSubclassOf<class APooledActor> ObjectClassToPool;

	// Populate the pool on begin play?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings")
    uint8 bFillPoolOnBeginPlay : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Optimization")
	FObjectPoolWarmUpSetting WarmUp;

	// References to the pooled actors
	UPROPERTY(BlueprintReadOnly, Category = "Object Pool")
	TArray<class APooledActor*> PooledActors;

private:
	TArray<TArray<int32>> PoolChunks;
	
	// Cached world reference
	UPROPERTY()
	UWorld* World;
};
