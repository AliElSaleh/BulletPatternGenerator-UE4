// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletPatternSpawner.generated.h"

UCLASS(BlueprintType, Blueprintable, HideCategories = ("Input", "Actor", "Replication", "Collision", "LOD"))
class BULLETPATTERNGENERATOR_API ABulletPatternSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletPatternSpawner();

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		class ABullet* SpawnBullet(class UBulletPattern_Base* BulletPattern, class UObjectPoolBase* BulletPool, const FVector& Direction, const float Speed);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void StartBulletPattern(class UBulletPattern_Base* BulletPattern);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void ResumeBulletPattern();
	
	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void StopBulletPattern();

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void ChangeBulletPattern(TSubclassOf<class UBulletPattern_Base> NewBulletPattern);

	UFUNCTION(BlueprintPure, Category = "Bullet Pattern Spawner")
		FName GetActiveBulletPatternName() const;

	UFUNCTION(BlueprintPure, Category = "Bullet Pattern Spawner")
		FORCEINLINE TSubclassOf<class UBulletPattern_Base> GetActiveBulletPatternClass() const { return BulletPatternClassFromEditor; }

	UFUNCTION(BlueprintPure, Category = "Bullet Pattern Spawner")
		FORCEINLINE class UBulletPattern_Base* GetActiveBulletPattern() const { return ActiveBulletPattern; }

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	// A list of all bullet patterns that this spawner can use
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Bullet Patterns", Category = "Bullet Pattern Spawner|Settings")
		TArray<TSubclassOf<class UBulletPattern_Base>> BulletPatternClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class URotatingMovementComponent* RotatingMovementComponent;
	
	// The bullet pattern to begin with
	UPROPERTY(EditInstanceOnly, DisplayName = "Bullet Pattern", Category = "Bullet Pattern Spawner|Settings")
		TSubclassOf<class UBulletPattern_Base> BulletPatternClassFromEditor;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Settings")
		uint8 bDisableSpawner : 1;

	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Pattern Spawner")
		void OnBulletPatternStarted();
		virtual void OnBulletPatternStarted_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Pattern Spawner")
		void OnBulletPatternStopped();
		virtual void OnBulletPatternStopped_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Pattern Spawner")
		void OnBulletPatternChanged();
		virtual void OnBulletPatternChanged_Implementation();
private:
	UPROPERTY()
		class UBulletPattern_Base* ActiveBulletPattern;

	UPROPERTY()
		TArray<class UBulletPattern_Base*> BulletPatterns;

	float ElapsedTime = 0.0f;
	uint8 bHasStarted : 1;
};
