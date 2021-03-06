// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "BulletPattern_SpinnableBase.h"
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

	// Retrieves the spin speed of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetSpinSpeed() const { return SpinSpeed; }
	
protected:
	void Tick(float DeltaTime) override;
	void UpdatePattern(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Pattern | Sine Wave")
		FRotator AngleSpread = FRotator(0.0f, 30.0f, 0.0f);

	// The speed of the 'spinning' effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Pattern | Sine Wave", meta = (ClampMin = 0.0f))
		float SpinSpeed = 1.0f;

	float ElapsedTime = 0.0f;

};
