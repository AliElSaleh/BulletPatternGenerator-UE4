// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "BulletPattern_ModifierBase.h"
#include "BulletPattern_Base.generated.h"

UENUM(BlueprintType)
enum EBulletDespawnSetting
{
	BDS_BulletLifespanExpired	UMETA(DisplayName="When bullet lifespan has expired"),
	BDS_OutOfScreen				UMETA(DisplayName="When bullet has left the screen"),
	BDS_MaxDistanceTravelled	UMETA(DisplayName="When bullet has travelled beyond the max distance")
};

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
	void Initialize();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "Begin Play", Category = "Bullet Pattern")
		void Broadcast_BeginPlay_Event();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "Tick", Category = "Bullet Pattern")
		void Broadcast_Tick_Event(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent, DisplayName = "Update Pattern", Category = "Bullet Pattern")
		void Broadcast_UpdatePattern_Event(float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "Bullet pattern")
		void SetStartingRotation(const FRotator& NewStartingRotation);

	UFUNCTION(BlueprintCallable, Category = "Bullet pattern")
		void ApplyModifier(class UBulletPattern_ModifierBase* Modifier);

	void CheckBulletsShouldDespawn();

	// Retrieves the speed that the bullets are using from this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetBulletSpeed() const { return BulletSpeed; }
	
	// Retrieves the fire-rate of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE float GetFireRate() const { return FireRate; }

	// Retrieves the name of this pattern
	UFUNCTION(BlueprintPure, Category = "Bullet pattern")
		FORCEINLINE FName GetPatternName() const { return PatternName; }

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
		void SpawnBulletInDirection(const FVector& InBulletDirection);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern")
		void ChangeBulletPool(TSubclassOf<UObjectPoolBase> NewBulletPool);

	UFUNCTION()
		void OnBulletMaxDistanceTravelled(class APooledActor* PooledActor);

	void OnBulletOutOfScreen(class APooledActor* PooledActor);
	void OnPatternLifetimeExpired();

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		float ElapsedTime = 0.0f;

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

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		FRotator StartingRotation = FRotator(0.0f);

	// The firing rate when spawning bullets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		TEnumAsByte<EBulletDespawnSetting> DespawnSetting = BDS_BulletLifespanExpired;

	// The firing rate when spawning bullets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings", meta = (ClampMin = 0.0f))
		float MaxBulletTravelDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		float PatternLifetime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern | Settings")
		TArray<TSubclassOf<class UBulletPattern_ModifierBase>> Modifiers;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		class ABulletPatternSpawner* BulletPatternSpawner;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		APawn* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern")
		TArray<class ABullet*> Bullets;

	UPROPERTY(BlueprintReadOnly, Category = "Bullet Pattern", DisplayName = "Active Bullet Pool")
		class UObjectPoolBase* BulletPoolToUse;

	uint8 bLifetimeExpired : 1;

private:
	void Broadcast_BeginPlay_Event_Implementation();
	void Broadcast_Tick_Event_Implementation(float DeltaTime);
	void Broadcast_UpdatePattern_Event_Implementation(float DeltaTime);
};
