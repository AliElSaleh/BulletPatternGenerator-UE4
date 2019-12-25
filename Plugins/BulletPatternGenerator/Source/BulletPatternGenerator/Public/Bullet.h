// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "Bullet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnBulletHitSignature, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBulletDestroyedSignature);

UCLASS(HideCategories=("Replication", "Input", "Actor", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API ABullet : public APooledActor
{
	GENERATED_BODY()
	
public:
	ABullet();

	// Broadcasted when this bullet actor has overlapped with another object
	UPROPERTY(BlueprintAssignable, Category = "Bullet|Events")
		FOnBulletHitSignature OnBulletHit;
	
	// Broadcasted when this bullet actor is about to be destroyed
	UPROPERTY(BlueprintAssignable, Category = "Bullet|Events")
		FOnBulletDestroyedSignature OnBulletDestroyed;
	
protected:
	void BeginPlay() override;
	void Destroyed() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

	// Called when this bullet actor has hit with another object
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet|Events")
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
		void OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Called when this bullet actor is about to be destroyed
	UFUNCTION(BlueprintNativeEvent, Category = "Bullet|Events")
		void OnDestroyed();
		void OnDestroyed_Implementation();

	// The normalized direction vector of the bullet (in other words, the direction it's heading in)
	UPROPERTY(VisibleAnywhere, Category = "Bullet Properties")
		FVector Direction = FVector(0.0f);

	// The acceleration of the bullet
	UPROPERTY(VisibleAnywhere, Category = "Bullet Properties")
		FVector Acceleration = FVector(0.0f);
	
	// The speed of the bullet
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float Speed = 100.0f;

	// The amount of damage to deal to a damagable actor
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float DamageAmount = 0.0f;

	// The amount of time (in seconds) this bullet will stay alive. 0.0 = Unlimited lifetime
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties", meta = (ClampMin = 0.0f))
		float MaxLifetime = 0.0f;

private:
	class UStaticMesh* SM_Bullet;
};
