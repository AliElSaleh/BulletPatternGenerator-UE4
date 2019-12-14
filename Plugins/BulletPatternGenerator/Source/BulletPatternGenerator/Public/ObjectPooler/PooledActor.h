// Copyright Ali El Saleh 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class BULLETPATTERNGENERATOR_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APooledActor();

	/**
	 * The pooled actor's custom begin play function. An event that is called by the user elsewhere (either in Blueprint or C++)
	 * Call this function after you've retrieved this actor from the pool.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pooled Actor", DisplayName = "Pooled Actor Begin Play")
		void PooledActor_BeginPlay();

	/**
	 * The pooled actor's custom end play function. An event that is called by the user elsewhere (either in Blueprint or C++)
	 * Call this function when you're done with this actor and you want to return it to the pool.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pooled Actor", DisplayName = "Pooled Actor End Play")
		void PooledActor_EndPlay();

	// Marks the actor in use. Enables tick (if specified), shows actor in game, enables collision (if specified), activates components and sets actor time dilation to 1.0
	UFUNCTION(BlueprintCallable, Category = "Pooled Actor")
		void MarkInUse();

	// Marks the actor not in use. Disables tick, hides actor in game, disables collision, deactivates components and sets actor time dilation to 0.0
	UFUNCTION(BlueprintCallable, Category = "Pooled Actor")
		void MarkNotInUse();

	/**
	 * Is this actor in use by its pool?
	 *
	 * @return True, if actor is being use. Otherwise, false.
	 */
	UFUNCTION(BlueprintPure, Category = "Pooled Actor")
		bool IsInUse() const { return bInUse; }

	/**
	 * Assigns this actor to the specified pool.
	 *
	 * @param InPoolToAssign	The object pool to assign this actor to
	 */
	void AssignToPool(class AObjectPoolBase* InPoolToAssign);

protected:
	void BeginPlay() override;
	void Destroyed() override;

	// Native implementation of 'PooledActor_BeginPlay' event
	virtual void PooledActor_BeginPlay_Implementation();

	// Native implementation of 'PooledActor_EndPlay' event
	virtual void PooledActor_EndPlay_Implementation();

	// Deactivates all children components
	UFUNCTION(BlueprintCallable, Category = "Pooled Actor")
		void DeactivateAllComponents();

	// Activates all children components
	UFUNCTION(BlueprintCallable, Category = "Pooled Actor")
		void ActivateAllComponents();

	/**
	 * Activates/Deactivates this actor based on parameter value
	 *
	 * @param bActive	 True, activates actor and all components. False, deactivates actor and all components
	 */
	void SetActive(bool bActive);

	// Should this actor ever be allowed to tick?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooled Actor")
		uint8 bEverAllowTick : 1;

	// Should this actor ever be allowed to test for collisions?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooled Actor")
		uint8 bEverAllowCollisions : 1;

	// All children components of this actor
	UPROPERTY(BlueprintReadOnly, Category = "Pooled Actor")
		TArray<UActorComponent*> Components;

	// Is this actor in use by its pool?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pooled Actor")
		uint8 bInUse : 1;

	// The pool that owns this actor
	class AObjectPoolBase* PoolOwner;
};
