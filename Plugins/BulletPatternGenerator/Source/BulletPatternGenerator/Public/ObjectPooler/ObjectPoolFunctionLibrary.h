// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectPoolFunctionLibrary.generated.h"

/**
 * A library of functions for the Object Pooler plugin
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UObjectPoolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static class AObjectPoolManager* GetObjectPoolManager(FName ManagerName);

	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static TArray<class AObjectPoolManager*> GetAllObjectPoolManagers();

	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static class UObjectPoolBase* GetObjectPool(FName PoolName);

	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static TArray<class UObjectPoolBase*> GetAllObjectPools();

	/**
	 * Marks the specified pooled actor not in use. Disables tick, hides actor in game, disables collision, deactivates components and sets actor time dilation to 0.0
	 *
	 * @param InPooledActor	 The pooled actor to mark not in use
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pooler")
		static void MarkActorNotInUse(class APooledActor* InPooledActor);

	/**
	 * Marks the specified pooled actor in use. Enables tick (if specified), shows actor in game, enables collision (if specified), activates components and sets actor time dilation to 1.0
	 *
	 * @param InPooledActor	 The pooled actor to mark in use
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pooler")
		static void MarkActorInUse(class APooledActor* InPooledActor);

	/**
	 * Tests to see if the specified actor is in use by the pool
	 *
	 * @param InPooledActor	The pooled actor to query
	 * @returns				True, if pooled actor is in use. Otherwise, false.
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static bool IsActorInUse(class APooledActor* InPooledActor);

	static TArray<class UObjectPoolBase*> ObjectPools;
	static TArray<class AObjectPoolManager*> ObjectPoolManagers;
};
