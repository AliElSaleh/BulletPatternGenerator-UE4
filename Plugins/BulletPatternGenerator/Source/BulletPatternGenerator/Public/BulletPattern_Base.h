// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BulletPattern_Base.generated.h"

/**
 * This class is a base class for all bullet pattern types.
 */
UCLASS(BlueprintType, Blueprintable)
class BULLETPATTERNGENERATOR_API UBulletPattern_Base : public UObject
{
	GENERATED_BODY()

protected:
	// Event when play begins for this bullet pattern class
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Pattern")
		void BeginPlay();
		virtual void BeginPlay_Implementation();

	// Event called every frame, if ticking is enabled
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Pattern")
		void Tick(float DeltaTime);
		virtual void Tick_Implementation(float DeltaTime);

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
