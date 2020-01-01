// Copyright Ali El Saleh 2019

#include "BulletPattern_Base.h"

#include "Engine/World.h"

UBulletPattern_Base::UBulletPattern_Base()
{
}

void UBulletPattern_Base::BeginPlay()
{

	ReceiveBeginPlay();
}

void UBulletPattern_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ResetAllProperties();
	
	ReceiveEndPlay(EndPlayReason);
}

void UBulletPattern_Base::Tick(const float DeltaTime)
{

	ReceiveTick(DeltaTime);
}

void UBulletPattern_Base::ResetAllProperties()
{
	ThisClass* Default = GetClass()->GetDefaultObject<ThisClass>();

	// We don't want to reset references to world object
	UWorld* World = GetWorld();
	const bool bIsPlayInEditor = World && World->IsPlayInEditor();

	// Iterate over properties
	for (TFieldIterator<UProperty> It(GetClass()); It; ++It)
	{
		UProperty* Prop = *It;
		UStructProperty* StructProp = Cast<UStructProperty>(Prop);

		// First see if it is a random stream, if so reset
		if (StructProp && StructProp->Struct && StructProp->Struct->GetFName() == "RandomStream")
		{
			FRandomStream* StreamPtr = StructProp->ContainerPtrToValuePtr<FRandomStream>(this);
			StreamPtr->Reset();
		}
		// If it is a blueprint exposed variable that is not editable per-instance, reset to default value
		else if (!Prop->ContainsInstancedObjectProperty())
		{
			const bool bExposedOnSpawn = bIsPlayInEditor && Prop->HasAnyPropertyFlags(CPF_ExposeOnSpawn);
			const bool bCanEditInstanceValue = !Prop->HasAnyPropertyFlags(CPF_DisableEditOnInstance) && Prop->HasAnyPropertyFlags(CPF_Edit);
			const bool bCanBeSetInBlueprints = Prop->HasAnyPropertyFlags(CPF_BlueprintVisible) && !Prop->HasAnyPropertyFlags(CPF_BlueprintReadOnly);

			if (!bExposedOnSpawn && 
				!bCanEditInstanceValue && 
				bCanBeSetInBlueprints &&
				!Prop->IsA<UDelegateProperty>() && 
				!Prop->IsA<UMulticastDelegateProperty>())
			{
				Prop->CopyCompleteValue_InContainer(this, Default);
				//Prop->ClearValue_InContainer(this);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *It->GetName())
			}
		}
	}
}
