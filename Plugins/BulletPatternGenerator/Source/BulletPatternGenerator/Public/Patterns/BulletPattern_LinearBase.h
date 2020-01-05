// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_Base.h"
#include "BulletPattern_LinearBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_LinearBase : public UBulletPattern_Base
{
	GENERATED_BODY()
	
public:
	UBulletPattern_LinearBase();

protected:
	void UpdatePattern(float DeltaTime) override;
};
