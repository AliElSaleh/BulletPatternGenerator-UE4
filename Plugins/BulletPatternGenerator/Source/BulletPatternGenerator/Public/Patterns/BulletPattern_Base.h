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

	UFUNCTION(BlueprintNativeEvent, DisplayName = "Begin Play", Category = "Bullet Pattern")
		void Broadcast_BeginPlay_Event();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "Tick", Category = "Bullet Pattern")
		void Broadcast_Tick_Event(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent, DisplayName = "Update Pattern", Category = "Bullet Pattern")
		void Broadcast_UpdatePattern_Event(float DeltaTime);
	
	// Retrieves the speed that the bullets are using from this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetBulletSpeed() const { return BulletSpeed; }
	
	// Retrieves the fire-rate of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetFireRate() const { return FireRate; }

	// Retrieves the bullet pool that this pattern is referencing
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE class UObjectPoolBase* GetBulletPool() const { return BulletPoolToUse; }

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void UpdatePattern(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern")
		void SpawnBullet();

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern")
		void ChangeBulletPool(TSubclassOf<UObjectPoolBase> NewBulletPool);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		FName PatternName = "Default Pattern";

	UPROPERTY(BlueprintReadWrite, Category = "Bullet Pattern")
		FVector BulletDirection;

	// The object pool to reference when spawning bullets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Bullet Pool to Use", Category = "Bullet Pattern | Settings")
		TSubclassOf<class UObjectPoolBase> BulletPoolClassToUse;
	
	// The speed of each bullet
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 1.0f))
		float BulletSpeed = 300.0f;

	// The firing rate when spawning bullets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 0.005f))
		float FireRate = 1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		class ABulletPatternSpawner* BulletPatternSpawner;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		APawn* Player;

	class UObjectPoolBase* BulletPoolToUse;

	float ElapsedTime = 0.0f;

private:
	void Broadcast_BeginPlay_Event_Implementation();
	void Broadcast_Tick_Event_Implementation(float DeltaTime);
	void Broadcast_UpdatePattern_Event_Implementation(float DeltaTime);
};