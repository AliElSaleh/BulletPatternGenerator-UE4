#pragma once

UENUM(BlueprintType)
enum class EObjectPoolReuseSetting : uint8
{
	// If pool is empty, allow reuse when retrieving an actor
	Reuse,
	
    //If pool is empty, do not allow reuse when retrieving an actor. Result will be null
    DoNotReuse,

    //If pool is empty, create new actor and add it to the pool
    CreateNewActor
};

UENUM(BlueprintType)
enum class EObjectPoolRetrieveActorResult : uint8
{
	Succeeded,
	Failed,
};
