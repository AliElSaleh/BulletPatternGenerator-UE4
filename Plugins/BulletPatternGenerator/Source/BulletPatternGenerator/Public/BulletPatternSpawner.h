// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletPatternSpawner.generated.h"

UCLASS(BlueprintType, Blueprintable, HideCategories = ("Input", "Actor", "Replication", "Collision", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API ABulletPatternSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletPatternSpawner();

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void SpawnBullet(class UBulletPattern_Base* BulletPattern, const FVector& Direction, const float Speed);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void StartBulletPattern(class UBulletPattern_Base* BulletPattern);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void ResumeBulletPattern();
	
	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void StopBulletPattern();

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void ChangeBulletPattern(TSubclassOf<class UBulletPattern_Base> NewBulletPattern);

	UFUNCTION(BlueprintCallable, Category = "Bullet Pattern Spawner")
		void ChangeObjectPool(TSubclassOf<class UObjectPoolBase> NewObjectPool);

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaTime) override;
	
	// A list of all bullet patterns that this spawner can use
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Bullet Patterns", Category = "Bullet Pattern Spawner|Settings")
		TArray<TSubclassOf<class UBulletPattern_Base>> BulletPatternClasses;

	// The active bullet pattern script
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Settings")
		TSubclassOf<class UObjectPoolBase> ObjectPoolToUse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Status")
		uint8 bHasStarted : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class URotatingMovementComponent* RotatingMovementComponent;
	
private:
	class UObjectPoolBase* ActiveBulletPool;

	UPROPERTY()
		class UBulletPattern_Base* ActiveBulletPattern;

	UPROPERTY()
		TArray<class UBulletPattern_Base*> BulletPatterns;

	float ElapsedTime = 0.0f;
};
