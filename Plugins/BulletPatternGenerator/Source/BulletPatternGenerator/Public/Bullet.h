// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "Bullet.generated.h"

UCLASS(HideCategories=("Replication", "Input", "Actor", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API ABullet : public APooledActor
{
	GENERATED_BODY()
	
public:
	ABullet();

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
		void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// A normalized direction vector value
	UPROPERTY(VisibleAnywhere, Category = "Bullet Properties")
		FVector Direction = FVector(0.0f);

	// A normalized direction vector value
	UPROPERTY(VisibleAnywhere, Category = "Bullet Properties")
		FVector Acceleration = FVector(0.0f);
	
	// A normalized direction vector value
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float Speed = 100.0f;

	// The amount of damage to deal to a damagable actor
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float DamageAmount = 0.0f;

private:
	class UStaticMesh* SM_Bullet;
};
