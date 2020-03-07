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

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Pattern | Lock-On")
		FString LockOnActorName = "None";

	UPROPERTY(EditDefaultsOnly, DisplayName = "Log Actor List to Console", Category = "Bullet Pattern | Lock-On")
		uint8 bLogActorList : 1;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern | Lock-On")
		AActor* LockOnTarget;

private:
#if WITH_EDITOR
	void LogActorListToConsole();
#endif
};
