// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "Bullet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnBulletHitSignature, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);

UCLASS(HideCategories=("Replication", "Input", "Actor", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API ABullet : public APooledActor
{
	GENERATED_BODY()
	
public:
	ABullet();

	// Broadcasted when this bullet actor has overlapped with another object
	UPROPERTY(BlueprintAssignable, Category = "Bullet|Events")
		FOnBulletHitSignature OnBulletHit;

	UFUNCTION(BlueprintCallable, Category = "Bullet")
		void SetupBehaviour(class UBulletPattern_Base* BulletPattern, FVector InDirection, float InSpeed);

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComponent;

	// Called when this bullet actor has hit with another object
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet|Events")
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		void OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// The normalized direction vector of the bullet (in other words, the direction it's heading in)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
		FVector Direction = FVector(0.0f);

	// The acceleration of the bullet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
		FVector Acceleration = FVector(0.0f);
	
	// The speed of the bullet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float Speed = 100.0f;

	// The amount of damage to deal to a damagable actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float DamageAmount = 0.0f;

private:
	class UStaticMesh* SM_Bullet;
};
