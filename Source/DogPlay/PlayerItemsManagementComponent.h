// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerItemsManagementComponent.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FInputActionPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> InputAction; // Replace with your actual Input Action type

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Subclass; // Replace UObject with your desired base class
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGPLAY_API UPlayerItemsManagementComponent : public UActorComponent
{
	GENERATED_BODY()
	
#pragma region Properties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	TArray<FInputActionPair> DefaultEquipment;

	UPROPERTY(BlueprintReadOnly,Category = "Items")
	TMap<uint8, TObjectPtr<AActor>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* UseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* UsingItemsMappingContext;

private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentUsageItemID)
	uint8 CurrentUsageItemID;

	uint8 LastUsageItemID;

	uint8 UniqueItemIDCounter = 0;

	bool bCanUseItem = true;

	bool bCanSwapItems = true;

#pragma endregion

#pragma region Methods
public:
	// Sets default values for this component's properties
	UPlayerItemsManagementComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentUsageItem() const;

	UFUNCTION(BlueprintCallable)
	AActor* GetItemByID(uint8 ID) const;
	
	UFUNCTION(BlueprintCallable)
	// Allows you to change the value of a locally control character about whether he can use the item
	void SetIsCanUseItem(bool bIsCanUseItem);
	
	UFUNCTION(BlueprintCallable)
	// Allows you to change the value of a locally control character about whether he can swap the items
	void SetIsCanSwapItems(bool bIsCanSwapItems);
	
protected:
	uint8 CreateAndRegisterItem(const TSubclassOf<AActor> &ItemSubclass);
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void CreateDefaultEquipmentItems();

	void UseCurrentItem();

	void SelectCurrentItem(uint8 ItemID);

#pragma endregion

#pragma region RPCmethods
	UFUNCTION()
	void OnRep_CurrentUsageItemID();
	
	UFUNCTION(Server, Unreliable)
	void Server_UseCurrentItem(FVector Location, FVector Direction);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_UseCurrentItem(FVector Location, FVector Direction);

	UFUNCTION(Server, Unreliable)
	void Server_SelectCurrentItem(uint8 ItemID);
	
#pragma endregion
	
};
