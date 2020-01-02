// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_Base.h"
#include "BulletPattern_SineWaveBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_SineWaveBase : public UBulletPattern_Base
{
	GENERATED_BODY()
	
public:
	UBulletPattern_SineWaveBase();
	
	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern|Sine Wave")
		FRotator AngleSpread = FRotator(0.0f, 30.0f, 0.0f);
};
