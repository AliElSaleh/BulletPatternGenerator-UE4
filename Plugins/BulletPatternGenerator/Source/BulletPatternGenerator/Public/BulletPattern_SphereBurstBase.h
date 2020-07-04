// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Patterns/BulletPattern_Base.h"
#include "BulletPattern_SphereBurstBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BULLETPATTERNGENERATOR_API UBulletPattern_SphereBurstBase : public UBulletPattern_Base
{
	GENERATED_BODY()

public:
	UBulletPattern_SphereBurstBase();
	
	void BeginPlay() override;

	void UpdatePattern(float DeltaTime) override;

protected:
	virtual void GenerateBulletDirections(int32 InNumOfWaysVertical, int32 NumOfWaysHorizontal);

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Settings")
		int32 NumOfWaysVertical = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Settings")
		int32 NumOfWaysHorizontal = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Settings")
		float MaxVerticalAngle = 360.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Settings")
		float MaxHorizontalAngle = 360.0f;
private:
	float Angle;
	float CurrentAngle;
	float CurrentPhi;

	TArray<FVector> Directions;
};
