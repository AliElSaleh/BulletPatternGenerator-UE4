// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "Patterns/BulletPattern_SineWaveBase.h"
#include "BulletPattern_SineWaveLockOn.generated.h"

/**
 * 
 */
UCLASS()
class BULLETPATTERNGENERATOR_API UBulletPattern_SineWaveLockOn : public UBulletPattern_SineWaveBase
{
	GENERATED_BODY()

public:
	UBulletPattern_SineWaveLockOn();

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Lock-On")
		FString LockOnActorName = "None";

	UPROPERTY(EditDefaultsOnly, DisplayName = "Log Actor List to Console", Category = "Bullet Pattern | Lock-On")
		uint8 bLogActorList : 1;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern | Lock-On")
		AActor* LockOnTarget;
};
