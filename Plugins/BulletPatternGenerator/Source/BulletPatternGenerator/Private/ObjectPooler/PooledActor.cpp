// Copyright Ali El Saleh 2019

#include "PooledActor.h"

#include "ObjectPooler/ObjectPoolBase.h"

#include "Engine/Public/TimerManager.h"

APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bEverAllowTick = true;
	bEverAllowCollisions = true;
}

void APooledActor::AssignToPool(AObjectPoolBase* InPoolToAssign)
{
	PoolOwner = InPoolToAssign;
}

void APooledActor::BeginPlay()
{
	Super::BeginPlay();

	Components = GetComponents().Array();
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
	MarkInUse();
}

void APooledActor::PooledActor_EndPlay_Implementation()
{
	MarkNotInUse();
	SetActorLocation(FVector(0.0f), false, nullptr, ETeleportType::TeleportPhysics);
}

void APooledActor::MarkInUse()
{
	SetActive(true);

	CustomTimeDilation = 1.0f;

	bInUse = true;
}

void APooledActor::MarkNotInUse()
{
	SetActive(false);

	CustomTimeDilation = 0.0f;

	bInUse = false;
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

		if (MaxLifespan > 0.0f)
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

		GetWorldTimerManager().ClearTimer(TH_LifeSpan);
	}
}

void APooledActor::ActivateAllComponents()
{
	for (auto Component : Components)
	{
		if (Component)
			Component->Activate(true);
	}
}

void APooledActor::DeactivateAllComponents()
{
	for (auto Component : Components)
	{
		if (Component)
			Component->Deactivate();
	}
}
