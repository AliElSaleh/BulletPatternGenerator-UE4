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

	// References to the pooled actors
	UPROPERTY(BlueprintReadOnly, Category = "Object Pool")
		TArray<class APooledActor*> PooledActorsInUse;

private:
	FVector CurrentLocation;
	FRotator CurrentRotation;

	// Cached world reference
	UWorld* World;
};
