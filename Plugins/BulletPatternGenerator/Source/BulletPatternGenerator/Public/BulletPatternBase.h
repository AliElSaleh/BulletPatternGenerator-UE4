// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BulletPatternBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BULLETPATTERNGENERATOR_API UBulletPatternBase : public UDataAsset
{
	GENERATED_BODY()

public:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 0.0f, ClampMax = 360.0f))
		float AngleSpread = 90.0f;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 1.0f))
		float BulletSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 0.005f))
		float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 0.0f))
		float SpinSpeed = 1.0f;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings")
	//	uint8 bReverse : 1;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings")
	//	uint8 bPingPong : 1;
};
