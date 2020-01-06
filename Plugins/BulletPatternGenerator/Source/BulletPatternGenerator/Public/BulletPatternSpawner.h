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
		TSubclassOf<class UBulletPattern_Base> GetActiveBulletPatternClass() const { return BulletPatternClass; }

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
	
	UPROPERTY(EditInstanceOnly, DisplayName = "Bullet Pattern", Category = "Bullet Pattern Spawner|Settings")
		TSubclassOf<class UBulletPattern_Base> BulletPatternClass;
private:
	UPROPERTY()
		class UBulletPattern_Base* ActiveBulletPattern;

	UPROPERTY()
		TArray<class UBulletPattern_Base*> BulletPatterns;

	float ElapsedTime = 0.0f;
	uint8 bHasStarted : 1;
};
