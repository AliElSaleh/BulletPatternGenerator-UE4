// Copyright Ali El Saleh 2020

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

	UFUNCTION(BlueprintPure, Category = "Object Pooler")
	static bool DoesObjectPoolExist(FName PoolName);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
    static int32 GetNumOfObjectPoolsInWorld();
	
	// Destroys all object pools in that were created
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
    static void DestroyAllObjectPools();

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

	static TArray<TArray<int32>> SplitPoolSize(int32 PoolSize, int32 InChunks);


	template<class ObjectClass>
	static TArray<ObjectClass*> GetAllObjectsOfClass();

	template<class ActorClass>
	static TArray<ActorClass*> GetAllActorsOfClass(UObject* WorldContextObject);
};

template <class ObjectClass>
TArray<ObjectClass*> UObjectPoolFunctionLibrary::GetAllObjectsOfClass()
{
	static_assert(TIsDerivedFrom<ObjectClass, UObject>::Value, "ObjectClass must be derived from a UObject class");
	
	TArray<ObjectClass*> Objects;

	for (TObjectIterator<ObjectClass> It; It; ++It)
	{
		Objects.Add(*It);
	}

	return Objects;
}

template <class ActorClass>
TArray<ActorClass*> UObjectPoolFunctionLibrary::GetAllActorsOfClass(UObject* WorldContextObject)
{
	static_assert(TIsDerivedFrom<ActorClass, AActor>::Value, "ActorClass must be derived from an AActor class");
	
	TArray<ActorClass*> Objects;

	for (TObjectIterator<ActorClass> It; It; ++It)
	{
		Objects.Add(*It);
	}

	return Objects;
}
