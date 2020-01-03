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

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Pattern|Sine Wave")
		FRotator AngleSpread = FRotator(0.0f, 30.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Pattern|Sine Wave")
		FRotator TargetRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern|Sine Wave")
		APawn* Player;
};
