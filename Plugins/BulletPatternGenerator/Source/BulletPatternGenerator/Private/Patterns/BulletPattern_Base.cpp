// Copyright Ali El Saleh 2019

#include "BulletPattern_Base.h"

#include "BulletPatternSpawner.h"

#include "Bullet.h"

#include "ObjectPooler/ObjectPoolFunctionLibrary.h"
#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

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

void UBulletPattern_Base::Initialize()
{
	Player = UGameplayStatics::GetPlayerPawn(this, 0);

	BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(BulletPoolClassToUse.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::BeginPlay()
{
}

void UBulletPattern_Base::Tick(float DeltaTime)
{
	if (DespawnSetting == BDS_LifespanExpired)
		return;

	for (int32 i = 0; i < Bullets.Num(); ++i)
	{
		switch (DespawnSetting)
		{
			case BDS_MaxDistanceTravelled:
			{
				const float DistanceFromSpawner = FVector::Distance(BulletPatternSpawner->GetActorLocation(), Bullets[i]->GetActorLocation());

				if (DistanceFromSpawner > MaxBulletTravelDistance)
					OnBulletMaxDistanceTravelled(Bullets[i]);
			}
			break;

			case BDS_OutOfScreen:
			{
				FVector2D ScreenPosition;
				UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(this, 0), Bullets[i]->GetActorLocation(), ScreenPosition);

				FVector2D ViewportSize;
				GEngine->GameViewport->GetViewportSize(ViewportSize);
					
				if (!Bullets[i]->WasRecentlyRendered() && 
					(ScreenPosition.X > ViewportSize.X || ScreenPosition.Y > ViewportSize.Y || ScreenPosition.X < 0.0f || ScreenPosition.Y < 0.0f))
				{
					OnBulletOutOfScreen(Bullets[i]);
				}
			}
			break;
		}
	}
}

void UBulletPattern_Base::UpdatePattern(float DeltaTime)
{
}

void UBulletPattern_Base::SpawnBullet()
{
	Bullets.Add(BulletPatternSpawner->SpawnBullet(this, BulletPoolToUse, BulletDirection, BulletSpeed));
}

void UBulletPattern_Base::SpawnBulletInDirection(const FVector& InBulletDirection)
{
	Bullets.Add(BulletPatternSpawner->SpawnBullet(this, BulletPoolToUse, InBulletDirection, BulletSpeed));
}

void UBulletPattern_Base::ChangeBulletPool(const TSubclassOf<UObjectPoolBase> NewBulletPool)
{
	if (NewBulletPool && UObjectPoolFunctionLibrary::DoesObjectPoolExist(NewBulletPool.GetDefaultObject()->GetPoolName()))
		BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(NewBulletPool.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::AssignSpawner(ABulletPatternSpawner* NewSpawner)
{
	BulletPatternSpawner = NewSpawner;
}

void UBulletPattern_Base::OnBulletMaxDistanceTravelled(class APooledActor* PooledActor)
{
	PooledActor->PooledActor_EndPlay();
	Bullets.Remove(Cast<ABullet>(PooledActor));
}

void UBulletPattern_Base::OnBulletOutOfScreen(APooledActor* PooledActor)
{
	PooledActor->PooledActor_EndPlay();
	Bullets.Remove(Cast<ABullet>(PooledActor));
}
