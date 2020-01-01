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

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaTime) override;

	// The active bullet pattern script
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Bullet Patterns", Category = "Bullet Pattern Spawner|Settings")
		TArray<TSubclassOf<class UBulletPattern_Base>> BulletPatternClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Pattern Spawner|Components")
		class URotatingMovementComponent* RotatingMovementComponent;
	
private:
	UPROPERTY()
		class UBulletPattern_Base* ActiveBulletPattern;

	float ElapsedTime = 0.0f;
};
