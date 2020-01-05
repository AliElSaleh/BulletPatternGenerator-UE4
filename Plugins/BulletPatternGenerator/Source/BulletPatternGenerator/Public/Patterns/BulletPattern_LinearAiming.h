// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_LinearBase.h"
#include "BulletPattern_LinearAiming.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_LinearAiming : public UBulletPattern_LinearBase
{
	GENERATED_BODY()

public:
	UBulletPattern_LinearAiming();

protected:
	void Tick(float DeltaTime) override;
};
