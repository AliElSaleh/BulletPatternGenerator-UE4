// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS(HideCategories=("Replication", "Input", "Actor", "LOD", "Cooking"))
class BULLETPATTERNGENERATOR_API ABullet final : public AActor
{
	GENERATED_BODY()
	
public:
	ABullet();

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
		void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	class UStaticMesh* SM_Bullet;
};
