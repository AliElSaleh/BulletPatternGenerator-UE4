// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolBase.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, HideCategories=("Input", "Rendering", "Actor", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API AObjectPoolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectPoolBase();

	/**
	 * Retrieves an actor from the pool that's not currently in use. If all actors in the pool are in use, a null reference will be returned.
	 *
	 * @return An actor reference from the pool. Null if all actors from the pool are in use
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
		class APooledActor* GetActorFromPool();
	
	/**
	 * Removes an actor from the pool. ONLY USE SPARINGLY. Call 'MarkNotInUse' from the pooled actor to return it to the pool.
	 * Alternatively, call 'MarkActorNotInUse' from an object pool.
	 *
	 * @param InPooledActor	 The pooled actor to remove from the pool
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		void RemoveActorFromPool(class APooledActor* InPooledActor);

	/**
	 * Marks the specified pooled actor not in use. Disables tick, hides actor in game, disables collision, deactivates components and sets actor time dilation to 0.0
	 *
	 * @param InPooledActor	 The pooled actor to mark not in use
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		void MarkActorNotInUse(class APooledActor* InPooledActor) const;

	/**
	 * Marks the specified pooled actor in use. Enables tick (if specified), shows actor in game, enables collision (if specified), activates components and sets actor time dilation to 1.0
	 *
	 * @param InPooledActor	 The pooled actor to mark in use
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		void MarkActorInUse(class APooledActor* InPooledActor) const;

	/**
	 * Tests to see if the specified actor is in use by the pool
	 *
	 * @param InPooledActor	The pooled actor to query
	 * @returns				True, if pooled actor is in use. Otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		bool IsActorInUse(class APooledActor* InPooledActor) const;

	/**
	 * Retrieves the name of the pool
	 *
	 * @returns				The pool's name
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		FName GetPoolName() const;

	/**
	 * Retrieves the size of the pool
	 *
	 * @returns				The pool's size
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		int32 GetPoolSize() const;

protected:
	void BeginPlay() override;

	/**
	 * Spawns an actor from the pool into the world. Marks the actor not in use as well
	 *
	 * @return A newly created pooled actor
	 */
	virtual class APooledActor* SpawnPooledObject();

	// The name of the pool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool Settings")
		FName PoolName = "Default";

	// The amount of objects that are allowed in the pool. 200,000 is the maximum that each pool can support
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool Settings", meta = (ClampMin = 1, ClampMax=200000))
		int32 PoolSize = 100;

	// The actor class to pool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool Settings", DisplayName = "Object to Pool")
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
