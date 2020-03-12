// Copyright Ali El Saleh 2019

#include "BulletPattern_ModifierBase.h"
#include "BulletPattern_Base.h"

UBulletPattern_ModifierBase::UBulletPattern_ModifierBase()
{
	bIsModifierApplied = false;
	BulletPattern = nullptr;
	ElapsedTime = 0.0f;
}

void UBulletPattern_ModifierBase::Apply_Implementation(class UBulletPattern_Base* InBulletPattern)
{
	BulletPattern = InBulletPattern;

	bIsModifierApplied = true;

	OnModifierApplied();
}

void UBulletPattern_ModifierBase::Reset_Implementation()
{
	BulletPattern = nullptr;
	bIsModifierApplied = false;
	ElapsedTime = 0.0f;
	bCanTick = false;
}

void UBulletPattern_ModifierBase::OnModifierApplied_Implementation()
{
}

void UBulletPattern_ModifierBase::Tick_Implementation(const float DeltaTime)
{
	ElapsedTime += DeltaTime;
}
