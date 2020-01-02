// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "BulletPattern_Base.generated.h"

/**
 * The base class for all bullet pattern types.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class BULLETPATTERNGENERATOR_API UBulletPattern_Base : public UObject
{
	GENERATED_BODY()

public:
	UBulletPattern_Base();

	void AssignSpawner(class ABulletPatternSpawner* NewSpawner);

	virtual void BeginPlay();
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason);
	virtual void Tick(float DeltaTime);
	virtual void UpdatePattern(float DeltaTime);

	// Retrieves the speed that the bullets are using from this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetBulletSpeed() const { return BulletSpeed; }
	
	// Retrieves the fire-rate of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetFireRate() const { return FireRate; }
	
	// Retrieves the spin speed of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetSpinSpeed() const { return SpinSpeed; }
	
protected:
	// Event when play begins for this bullet pattern class
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Begin Play", Category = "Bullet Pattern")
		void ReceiveBeginPlay();

	// Event to notify blueprints this actor is being deleted or removed from a level
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "End Play", Category = "Bullet Pattern")
		void ReceiveEndPlay(EEndPlayReason::Type EndPlayReason);

	// Event called every frame, if ticking is enabled
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Tick", Category = "Bullet Pattern")
		void ReceiveTick(float DeltaTime);

	// Event called every 'fire-rate' seconds, if ticking is enabled
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Update Pattern", Category = "Bullet Pattern")
		void ReceiveUpdatePattern(float DeltaTime);

	void ResetAllProperties();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		FName PatternName = "Default Pattern";

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		FVector BulletDirection;

	// The speed of each bullet
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 1.0f))
		float BulletSpeed = 300.0f;

	// The firing rate when spawning bullets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 0.005f))
		float FireRate = 1.0f;

	// The speed of the 'spinning' effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 0.0f))
		float SpinSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		class ABulletPatternSpawner* BulletPatternSpawner;

	float ElapsedTime = 0.0f;
};
