// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BulletPatternFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPatternFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Bullet Pattern | Helpers")
	static FVector2D CalculatePositionOnCircle(FVector2D Origin, float Radius, float Angle);

	UFUNCTION(BlueprintPure, Category = "Bullet Pattern | Helpers")
	static FVector CalculateLocationOnSphere(FVector Origin, float Radius, float Angle, float Phi);
};
