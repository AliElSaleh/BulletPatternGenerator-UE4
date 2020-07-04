// Copyright Ali El Saleh 2020

#include "PooledActor.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/Public/TimerManager.h"

APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bEverAllowTick = true;
	bEverAllowCollisions = true;

	bFindCameraComponentWhenViewTarget = false;
}

void APooledActor::AssignToPool(UObjectPoolBase* InPoolToAssign)
{
	if (!InPoolToAssign)
		return;

	if (PoolOwner)
		PoolOwner->RemoveActorFromPool(this);

	PoolOwner = InPoolToAssign;
}

void APooledActor::AssignToPool(UObjectPoolComponent* InPoolToAssign)
{
	//if (!InPoolToAssign)
	//	return;
//
	//if (PoolOwner)
	//	PoolOwner->RemoveActorFromPool(this);
//
	//PoolOwner = InPoolToAssign;
}

void APooledActor::Destroyed()
{
	if (PoolOwner)
		PoolOwner->RemoveActorFromPool(this);
}

void APooledActor::OnLifeSpanExpired()
{
	PooledActor_EndPlay();
}

void APooledActor::PooledActor_BeginPlay_Implementation()
{
	MarkInUse(true);
}

void APooledActor::PooledActor_EndPlay_Implementation()
{
	MarkNotInUse(true);
	//SetActorLocation(FVector(0.0f), false, nullptr, ETeleportType::TeleportPhysics);
}

void APooledActor::MarkInUse(const bool bBroadcast)
{
	SetActive(true);

	CustomTimeDilation = 1.0f;

	bInUse = true;

	if (bBroadcast)
		InUse.Broadcast(this);
}

void APooledActor::MarkNotInUse(const bool bBroadcast)
{
	SetActive(false);

	CustomTimeDilation = 0.0f;

	bInUse = false;

	if (bBroadcast)
		NotInUse.Broadcast(this);
}

void APooledActor::SetActive(const bool bActive)
{
	if (bActive)
	{
		// Start ticking
		SetActorTickEnabled(bEverAllowTick);

		// Show the actor
		SetActorHiddenInGame(false);

		// Enable collision on every component
		SetActorEnableCollision(bEverAllowCollisions);

		ActivateAllComponents();
		
		if (MaxLifespan > 0.0f && IsInGameThread())
			GetWorldTimerManager().SetTimer(TH_LifeSpan, this, &APooledActor::OnLifeSpanExpired, MaxLifespan);
	}
	else
	{
		// Stop ticking
		SetActorTickEnabled(false);

		// Hide the actor
		SetActorHiddenInGame(true);

		// Disables collision on every component
		SetActorEnableCollision(false);

		DeactivateAllComponents();

		if (IsInGameThread())
			GetWorldTimerManager().ClearTimer(TH_LifeSpan);
	}
}

void APooledActor::ActivateAllComponents()
{
	TArray<UActorComponent*> Components = GetComponents().Array();
	
	for (auto Component : Components)
	{
		if (Component)
			Component->Activate(true);
	}
}

void APooledActor::DeactivateAllComponents()
{
	TArray<UActorComponent*> Components = GetComponents().Array();

	for (auto Component : Components)
	{
		if (Component)
			Component->Deactivate();
	}
}
