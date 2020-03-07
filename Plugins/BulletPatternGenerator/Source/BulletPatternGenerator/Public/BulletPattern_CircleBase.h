// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Patterns/BulletPattern_Base.h"
#include "BulletPattern_CircleBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_CircleBase : public UBulletPattern_Base
{
	GENERATED_BODY()

public:
	UBulletPattern_CircleBase();

protected:
	void Tick(float DeltaTime) override;
};
