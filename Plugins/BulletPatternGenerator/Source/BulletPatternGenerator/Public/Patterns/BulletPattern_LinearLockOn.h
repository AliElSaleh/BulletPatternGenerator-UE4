// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_LinearBase.h"
#include "BulletPattern_LinearLockOn.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_LinearLockOn : public UBulletPattern_LinearBase
{
	GENERATED_BODY()

public:
	UBulletPattern_LinearLockOn();

protected:
	void BeginPlay() override;
	void UpdatePattern(float DeltaTime) override;
};
