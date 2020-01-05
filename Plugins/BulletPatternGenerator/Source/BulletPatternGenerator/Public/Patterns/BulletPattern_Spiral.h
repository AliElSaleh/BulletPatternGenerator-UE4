// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Patterns/BulletPattern_SpinnableBase.h"
#include "BulletPattern_Spiral.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_Spiral : public UBulletPattern_SpinnableBase
{
	GENERATED_BODY()
	
public:
	UBulletPattern_Spiral();

protected:
	void Tick(float DeltaTime) override;
};
