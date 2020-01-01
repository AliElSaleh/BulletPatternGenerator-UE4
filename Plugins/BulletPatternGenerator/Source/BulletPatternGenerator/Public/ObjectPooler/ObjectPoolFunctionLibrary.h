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
		static class AObjectPoolBase* GetObjectPool(const UObject* WorldContextObject, FName PoolName);

	UFUNCTION(BlueprintPure, Category = "Object Pooler")
		static TArray<class AObjectPoolBase*> GetAllObjectPools(const UObject* WorldContextObject);
};
