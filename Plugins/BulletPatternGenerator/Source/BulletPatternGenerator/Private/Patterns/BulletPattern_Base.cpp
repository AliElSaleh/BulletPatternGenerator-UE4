// Copyright Ali El Saleh 2019

#include "BulletPattern_Base.h"

#include "BulletPatternSpawner.h"

#include "Bullet.h"

#include "ObjectPooler/ObjectPoolFunctionLibrary.h"
#include "ObjectPooler/ObjectPoolBase.h"

#include "Kismet/GameplayStatics.h"

UBulletPattern_Base::UBulletPattern_Base()
{
}

void UBulletPattern_Base::Broadcast_BeginPlay_Event_Implementation()
{
	BeginPlay();
}

void UBulletPattern_Base::Broadcast_Tick_Event_Implementation(const float DeltaTime)
{
	Tick(DeltaTime);
}

void UBulletPattern_Base::Broadcast_UpdatePattern_Event_Implementation(const float DeltaTime)
{
	UpdatePattern(DeltaTime);
}

void UBulletPattern_Base::BeginPlay()
{
	Player = UGameplayStatics::GetPlayerPawn(this, 0);

	BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(BulletPoolClassToUse.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::Tick(float DeltaTime)
{
}

void UBulletPattern_Base::UpdatePattern(float DeltaTime)
{
	//BulletPatternSpawner->SpawnBullet(this, BulletDirection, BulletSpeed);
}

void UBulletPattern_Base::SpawnBullet()
{
	BulletPatternSpawner->SpawnBullet(this, BulletPoolToUse, BulletDirection, BulletSpeed);
}

void UBulletPattern_Base::ChangeBulletPool(const TSubclassOf<UObjectPoolBase> NewBulletPool)
{
	if (NewBulletPool)
		BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(NewBulletPool.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::AssignSpawner(ABulletPatternSpawner* NewSpawner)
{
	BulletPatternSpawner = NewSpawner;
}
