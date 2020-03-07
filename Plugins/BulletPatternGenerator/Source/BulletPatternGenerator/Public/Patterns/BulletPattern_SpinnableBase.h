// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_Base.h"
#include "BulletPattern_SpinnableBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BULLETPATTERNGENERATOR_API UBulletPattern_SpinnableBase : public UBulletPattern_Base
{
	GENERATED_BODY()

public:
	UBulletPattern_SpinnableBase();

protected:
	void UpdatePattern(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Pattern | Spinnable")
		FRotator RotationRate = FRotator(0.0f, 100.0f, 0.0f);
};
