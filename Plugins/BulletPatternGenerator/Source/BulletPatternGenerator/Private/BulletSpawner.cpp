// Copyright Ali El Saleh 2019


#include "BulletSpawner.h"

// Sets default values
ABulletSpawner::ABulletSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABulletSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

