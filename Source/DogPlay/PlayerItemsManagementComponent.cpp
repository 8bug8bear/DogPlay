// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerItemsManagementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractingWithObjectsInterface.h"
#include "ItemsManagementInterface.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPlayerItemsManagementComponent::UPlayerItemsManagementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UPlayerItemsManagementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlayerItemsManagementComponent, CurrentUsageItemID);
}

AActor* UPlayerItemsManagementComponent::GetCurrentUsageItem() const
{
	return GetItemByID(CurrentUsageItemID);
}

AActor* UPlayerItemsManagementComponent::GetItemByID(const uint8 ID) const
{
	if(auto* FoundItemRef = Items.Find(ID))
	{
		return *FoundItemRef;
	}
	return nullptr;
}

void UPlayerItemsManagementComponent::SetIsCanUseItem(const bool bIsCanUseItem)
{
	if(IItemsManagementInterface::Execute_IsOwnerLocallyControl(GetOwner()))
	{
		bCanUseItem = bIsCanUseItem;
	}
}

void UPlayerItemsManagementComponent::SetIsCanSwapItems(const bool bIsCanSwapItems)
{
	if(IItemsManagementInterface::Execute_IsOwnerLocallyControl(GetOwner()))
	{
		bCanSwapItems = bIsCanSwapItems;
	}
}

uint8 UPlayerItemsManagementComponent::CreateAndRegisterItem(const TSubclassOf<AActor> &ItemSubclass)
{
	if(!IsValid(ItemSubclass))
	{
		return INDEX_NONE;
	}

	FActorSpawnParameters ActorSpawnParameters = FActorSpawnParameters();;
	ActorSpawnParameters.Owner = GetOwner();
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* NewItem = GetWorld()->SpawnActor<AActor>(ItemSubclass, ActorSpawnParameters);
	if(IsValid(NewItem))
	{
		FName OutSocketName;
		USceneComponent* SceneComponent = IItemsManagementInterface::Execute_GetComponentToAttach(GetOwner(), OutSocketName);
		NewItem->AttachToComponent(SceneComponent , FAttachmentTransformRules::KeepRelativeTransform, OutSocketName);
		const uint8 NewItemID = UniqueItemIDCounter;
		UniqueItemIDCounter++;
		Items.Emplace(NewItemID , NewItem);
		IInteractingWithObjectsInterface::Execute_SetUniqueItemID(NewItem, NewItemID);
		return NewItemID;
	}
	
	return INDEX_NONE;
}

// Called when the game starts
void UPlayerItemsManagementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = IItemsManagementInterface::Execute_GetOwnerController(GetOwner()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(UsingItemsMappingContext, 1);
		}
	
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &UPlayerItemsManagementComponent::UseCurrentItem);
		}
	}

	CreateDefaultEquipmentItems();
}

void UPlayerItemsManagementComponent::CreateDefaultEquipmentItems()
{
	uint8 FirstItemID = 255;
	for(const auto &Item : DefaultEquipment)
	{
		const uint8 NewItemID = CreateAndRegisterItem(Item.Subclass);
		if(NewItemID != INDEX_NONE)
		{
			IInteractingWithObjectsInterface::Execute_SetObjectVisibility(GetItemByID(NewItemID), false);
			if (const APlayerController* PlayerController = IItemsManagementInterface::Execute_GetOwnerController(GetOwner()))
			{
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
				{
					EnhancedInputComponent->BindAction(Item.InputAction, ETriggerEvent::Triggered, this, &UPlayerItemsManagementComponent::SelectCurrentItem, NewItemID);
				}
			}
			if(FirstItemID == 255)
			{
				FirstItemID = NewItemID;
			}
		}
	}
	if(FirstItemID != 255)
	{
		CurrentUsageItemID = FirstItemID;
		LastUsageItemID = CurrentUsageItemID;
		IInteractingWithObjectsInterface::Execute_SetObjectVisibility(GetCurrentUsageItem(), true);
	}
}

void UPlayerItemsManagementComponent::UseCurrentItem()
{
	if(!bCanUseItem || !GetCurrentUsageItem())
	{
		return;
	}

	FVector InLocation;
	FRotator OutRotation;

	const APlayerController* Controllet = IItemsManagementInterface::Execute_GetOwnerController(GetOwner());
	if(Controllet)
	{
		Controllet->GetPlayerViewPoint(InLocation, OutRotation);
	}
	const FVector InDirection = OutRotation.RotateVector(FVector::ForwardVector);

	IInteractingWithObjectsInterface::Execute_UseObject(GetCurrentUsageItem(), InLocation, InDirection);
	if(IItemsManagementInterface::Execute_IsOwnerLocallyControl(GetOwner()) && GetWorld()->GetNetMode() == NM_Client)
	{
		Server_UseCurrentItem(InLocation, InDirection);
	}
}

void UPlayerItemsManagementComponent::SelectCurrentItem(const uint8 ItemID)
{
	if(CurrentUsageItemID == ItemID || !bCanSwapItems)
	{
		return;
	}
	if(IItemsManagementInterface::Execute_IsOwnerLocallyControl(GetOwner()))
	{
		Server_SelectCurrentItem(ItemID);
	}
}

void UPlayerItemsManagementComponent::OnRep_CurrentUsageItemID()
{
	if(GetItemByID(LastUsageItemID))
	{
		IInteractingWithObjectsInterface::Execute_SetObjectVisibility(GetItemByID(LastUsageItemID), false);
	}
	if(GetItemByID(CurrentUsageItemID))
	{
		IInteractingWithObjectsInterface::Execute_SetObjectVisibility(GetItemByID(CurrentUsageItemID), true);
	}
	LastUsageItemID = CurrentUsageItemID;
}

void UPlayerItemsManagementComponent::Server_UseCurrentItem_Implementation(FVector Location, FVector Direction)
{
	Multicast_UseCurrentItem(Location, Direction);
}

void UPlayerItemsManagementComponent::Multicast_UseCurrentItem_Implementation(FVector Location, FVector Direction)
{
	if(!IItemsManagementInterface::Execute_IsOwnerLocallyControl(GetOwner()))
	{
		IInteractingWithObjectsInterface::Execute_UseObject(GetCurrentUsageItem(), Location, Direction);
	}
}

void UPlayerItemsManagementComponent::Server_SelectCurrentItem_Implementation(uint8 ItemID)
{
	if(CurrentUsageItemID != ItemID)
	{
		CurrentUsageItemID = ItemID;
	}
}
