// Copyright Ali El Saleh 2019

#include "BulletPattern_Base.h"

#include "BulletPatternSpawner.h"

#include "ObjectPooler/ObjectPoolFunctionLibrary.h"
#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/World.h"

UBulletPattern_Base::UBulletPattern_Base()
{
}

void UBulletPattern_Base::BeginPlay()
{
	BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(this, BulletPoolClassToUse.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

void UBulletPattern_Base::Tick(const float DeltaTime)
{

}

void UBulletPattern_Base::UpdatePattern(const float DeltaTime)
{
	BulletPatternSpawner->SpawnBullet(this, BulletDirection, BulletSpeed);
}

void UBulletPattern_Base::AssignSpawner(ABulletPatternSpawner* NewSpawner)
{
	BulletPatternSpawner = NewSpawner;
}
