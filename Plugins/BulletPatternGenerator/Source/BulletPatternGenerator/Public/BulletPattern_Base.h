// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BulletPattern_Base.generated.h"

/**
 * The base class for all bullet pattern types.
 */
UCLASS(BlueprintType, Blueprintable)
class BULLETPATTERNGENERATOR_API UBulletPattern_Base : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

protected:
	// Event when play begins for this bullet pattern class
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Begin Play", Category = "Bullet Pattern")
		void ReceiveBeginPlay();

	// Event called every frame, if ticking is enabled
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Tick", Category = "Bullet Pattern")
		void ReceiveTick(float DeltaTime);

	// The speed of each bullet
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 1.0f))
		float BulletSpeed = 300.0f;

	// The firing rate when spawning bullets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 0.005f))
		float FireRate = 1.0f;

	// The speed of the 'spinning' effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern Settings", meta = (ClampMin = 0.0f))
		float SpinSpeed = 1.0f;
};
