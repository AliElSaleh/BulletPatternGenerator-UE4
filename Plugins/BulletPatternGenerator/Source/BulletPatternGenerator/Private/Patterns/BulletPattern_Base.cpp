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

void UBulletPattern_Base::BeginPlay()
{
	bLifetimeExpired = false;
	ElapsedTime = 0.0f;

	Modifiers.Empty();
	for (auto Modifier : ModifierTypes)
	{
		auto ModifierObject = NewObject<UBulletPattern_ModifierBase>(this, Modifier.Key.Get(), Modifier.Key->GetFName(), RF_NoFlags, Modifier.Key.GetDefaultObject(), true);
		ModifierObject->bIsModifierApplied = false;

		Modifiers.Add(ModifierObject);
	}

	if (bApplyAllModifiersOnBeginPlay)
		ApplyAllModifiers();
}

void UBulletPattern_Base::Tick(const float DeltaTime)
{
	if (!bLifetimeExpired && ElapsedTime > PatternLifetime && PatternLifetime != 0.0f)
	{
		OnPatternLifetimeExpired();
	}

	for (auto Modifier : Modifiers)
	{
		if (Modifier && Modifier->CanTick())
			Modifier->Tick(DeltaTime);
	}

	ElapsedTime += DeltaTime;
}

void UBulletPattern_Base::UpdatePattern(float DeltaTime)
{
}

void UBulletPattern_Base::Initialize()
{
	Player = UGameplayStatics::GetPlayerPawn(this, 0);

	BulletPoolToUse = UObjectPoolFunctionLibrary::GetObjectPool(BulletPoolClassToUse.GetDefaultObject()->GetPoolName());
}

void UBulletPattern_Base::SetStartingRotation(const FRotator& NewStartingRotation)
{
	StartingRotation = NewStartingRotation;
	BulletDirection = NewStartingRotation.Vector();
}

void UBulletPattern_Base::ApplyModifier(const int32 Index)
{
	if (bApplyAllModifiersOnBeginPlay || Index >= Modifiers.Num())
		return;

	TArray<bool> ModifierTypes_Values;
	ModifierTypes.GenerateValueArray(ModifierTypes_Values);
	
	if (ModifierTypes_Values.IsValidIndex(Index) && ModifierTypes_Values[Index] && !Modifiers[Index]->bIsModifierApplied)
		Modifiers[Index]->Apply(this);
}

void UBulletPattern_Base::RemoveModifier(const int32 Index)
{
	if (Index >= Modifiers.Num())
		return;

	if (Modifiers.IsValidIndex(Index))
		Modifiers[Index]->Reset();
}

void UBulletPattern_Base::ApplyAllModifiers()
{
	for (auto Modifier : Modifiers)
	{
		if (Modifier)
			Modifier->Apply(this);
	}
}

void UBulletPattern_Base::RemoveAllModifiers()
{
	for (auto Modifier : Modifiers)
	{
		if (Modifier)
			Modifier->Reset();
	}
}

void UBulletPattern_Base::CheckBulletsShouldDespawn()
{
	if (bLifetimeExpired && Bullets.Num() == 0)
	{
		BulletPatternSpawner->StopBulletPattern();
		return;
	}

	switch (DespawnSetting)
	{
		case BDS_BulletLifespanExpired:
		break;
		
		case BDS_MaxDistanceTravelled:
		{
			for (int32 i = 0; i < Bullets.Num(); ++i)
			{
				const float DistanceFromSpawner = FVector::Distance(BulletPatternSpawner->GetActorLocation(), Bullets[i]->GetActorLocation());

				if (DistanceFromSpawner > MaxBulletTravelDistance)
					OnBulletMaxDistanceTravelled(Bullets[i]);
			}
		}
		break;

		case BDS_OutOfScreen:
		{
			for (int32 i = 0; i < Bullets.Num(); ++i)
			{
				FVector2D BulletPositionOnScreen;
				UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(this, 0), Bullets[i]->GetActorLocation(), BulletPositionOnScreen);

				FVector2D ViewportSize;
				GEngine->GameViewport->GetViewportSize(ViewportSize);
					
				if (!Bullets[i]->WasRecentlyRendered() && 
					(BulletPositionOnScreen.X > ViewportSize.X || BulletPositionOnScreen.Y > ViewportSize.Y || BulletPositionOnScreen.X < 0.0f || BulletPositionOnScreen.Y < 0.0f))
				{
					OnBulletOutOfScreen(Bullets[i]);
				}
			}
		}
		break;

		default:
		break;
	}
}

class ABullet* UBulletPattern_Base::SpawnBullet()
{
	ABullet* Bullet = BulletPatternSpawner->SpawnBullet(this, BulletPoolToUse, BulletDirection, BulletSpeed);

	if (Bullet)
		Bullets.Add(Bullet);

	return Bullet;
}

class ABullet* UBulletPattern_Base::SpawnBulletInDirection(const FVector& InBulletDirection)
{
	ABullet* Bullet = BulletPatternSpawner->SpawnBullet(this, BulletPoolToUse, InBulletDirection, BulletSpeed);

	if (Bullet)
		Bullets.Add(Bullet);

	return Bullet;
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

void UBulletPattern_Base::OnPatternLifetimeExpired()
{
	bLifetimeExpired = true;

	BulletPatternSpawner->StopBulletPattern();
}
