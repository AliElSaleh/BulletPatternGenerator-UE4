// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolBase.generated.h"

UENUM(BlueprintType)
enum EObjectPoolReuseSetting
{
	OPRS_Reuse			UMETA(DisplayName="If pool is empty, allow reuse when retrieving an actor"),
	OPRS_DoNotReuse		UMETA(DisplayName="If pool is empty, do not allow reuse when retrieving an actor. Result will be null"),
	OPRS_CreateNewActor	UMETA(DisplayName="If pool is empty, create new actor and add it to the pool")
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class BULLETPATTERNGENERATOR_API UObjectPoolBase : public UObject
{
	GENERATED_BODY()
	
public:	
	UObjectPoolBase();

	/**
	 * Retrieves an actor from the pool that's not currently in use. If all actors in the pool are in use, a null reference will be returned.
	 *
	 * @return An actor reference from the pool. Null if there are no actors in the pool
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
		virtual class APooledActor* GetActorFromPool();
	
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
		bool IsPoolEmpty() const { return PooledActors.Num() == 0; }

	void BeginPlay();

protected:
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings", meta = (ClampMin = 1, ClampMax = 200000))
		int32 PoolSize = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings")
		TEnumAsByte<EObjectPoolReuseSetting> ReuseSetting = OPRS_Reuse;

	// The actor class to pool
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pool Settings", DisplayName = "Object to Pool")
		TSubclassOf<class APooledActor> ObjectClassToPool;

	// References to the pooled actors
	UPROPERTY(BlueprintReadOnly, Category = "Object Pool")
		TArray<class APooledActor*> PooledActors;

private:
	FVector CurrentLocation;
	FRotator CurrentRotation;

	// Cached world reference
	UWorld* World;
};
