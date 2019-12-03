// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class BULLETPATTERNGENERATOR_API ABullet final : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
