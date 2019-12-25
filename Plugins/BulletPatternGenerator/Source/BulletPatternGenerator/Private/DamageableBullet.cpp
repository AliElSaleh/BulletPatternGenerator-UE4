// Copyright Ali El Saleh 2019


#include "DamageableBullet.h"

ADamageableBullet::ADamageableBullet()
	: ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bCanBeDamaged = true;
}
