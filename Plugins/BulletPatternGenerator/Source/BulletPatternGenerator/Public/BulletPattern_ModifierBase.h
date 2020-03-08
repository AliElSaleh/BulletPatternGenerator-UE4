// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BulletPattern_ModifierBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class BULLETPATTERNGENERATOR_API UBulletPattern_ModifierBase : public UObject
{
	GENERATED_BODY()

public:
	UBulletPattern_ModifierBase();

	UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
	void Apply(class UBulletPattern_Base* InBulletPattern);
	virtual void Apply_Implementation(class UBulletPattern_Base* InBulletPattern);

	UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
	void Reset();
	virtual void Reset_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
	void OnModifierApplied();
	virtual void OnModifierApplied_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
	void Tick(float DeltaTime);
	virtual void Tick_Implementation(float DeltaTime);

	UFUNCTION(BlueprintPure, Category = "Modifier")
	FORCEINLINE bool CanTick() const { return bCanTick && bIsModifierApplied; }

	UPROPERTY(BlueprintReadOnly, Category = "Modifier")
	uint8 bIsModifierApplied : 1;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		FName ModifierName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	uint8 bCanTick : 1;

	UPROPERTY(BlueprintReadWrite, Category = "Modifier")
	float ElapsedTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Modifier")
	class UBulletPattern_Base* BulletPattern;
};
