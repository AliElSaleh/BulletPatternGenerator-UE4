#pragma once

#include "ObjectPoolerStructs.generated.h"

USTRUCT(BlueprintType)
struct FObjectPoolWarmUpSetting
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, Category = "Object Pool Warmup Settings")
    uint8 bEnabled : 1;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool Warmup Settings", meta = (EditCondition = "bEnabled", ClampMin = 1))
    uint16 WarmUpAcross = 2;

	uint8 bWarmUpComplete : 1;
	
	uint16 WarmUpCounter = 0;
};
