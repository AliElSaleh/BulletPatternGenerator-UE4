// Copyright Ali El Saleh 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ObjectPoolManager.generated.h"

/**
 * High-level manager class for all object pools in the world
 */
UCLASS(NotBlueprintable, HideCategories=("Actor", "LOD", "Cooking", "Replication"))
class BULLETPATTERNGENERATOR_API AObjectPoolManager final : public AInfo
{
	GENERATED_BODY()
	
public:
	AObjectPoolManager();

	/**
	 * Retrieves a pool object from the world via the specified name
	 *
	 * @param InPoolName	The object pool's name to search for
	 * @returns				If found, return an object pool actor pointer. Otherwise, null
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	class UObjectPoolBase* GetPool(FString InPoolName);

	/**
	 * Retrieves the specified object pool's name via an object pool actor pointer
	 *
	 * @param InObjectPool	The object pool to search for
	 * @returns If found, return the object pool's name. Otherwise, return "Not Valid"
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	FString GetPoolName(class UObjectPoolBase* InObjectPool);

	/**
	 * Retrieves the name of this object pool manager
	 *
	 * @returns The name of this manager object
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	FName GetManagerName() const { return ManagerName; }

	/**
	 * Retrieves the specified object pool's class via an object pool actor pointer
	 *
	 * @param InObjectPool	The object pool to search for
	 * @returns				If found, return the object pool's class type. Otherwise, return null
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	TSubclassOf<class UObjectPoolBase> GetPoolClass(class UObjectPoolBase* InObjectPool);

	/**
	 * Retrieves the specified object pool's class via the specified name
	 *
	 * @param InPoolName	The object pool's name to search for
	 * @returns				If found, return the object pool's class type. Otherwise, return null
	 */
	UFUNCTION(BlueprintPure, Category = "Object Pool")
	TSubclassOf<class UObjectPoolBase> GetPoolClassFromString(FString InPoolName);

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void PostInitializeComponents() override;
	
	// Spawns all object pools in the 'ObjectPools' list
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void SpawnAllObjectPools();
	
	/**
	 * Spawns a specific object pool via the specified sub-class
	 *
	 * @param InPoolClass	The sub-class of AObjectPoolBase to spawn
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void SpawnObjectPool(TSubclassOf<UObjectPoolBase> InPoolClass);

	UPROPERTY(EditInstanceOnly, Category = "Object Pool Settings")
	FName ManagerName = "Default Object Pool Manager";

	// The list of object pools to spawn. Assign a name to an object pool to later retrieve it using the name at runtime
	UPROPERTY(EditInstanceOnly, Category = "Object Pool Settings", DisplayName = "Object Pools")
	TArray<TSubclassOf<class UObjectPoolBase>> ObjectPoolClasses;
	
};
