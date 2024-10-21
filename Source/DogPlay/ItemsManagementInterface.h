// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemsManagementInterface.generated.h"

class UPlayerItemsManagementComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemsManagementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DOGPLAY_API IItemsManagementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	UPlayerItemsManagementComponent* GetPlayerItemsManagementComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	APlayerController* GetOwnerController() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	bool IsOwnerLocallyControl() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	USceneComponent* GetComponentToAttach(FName &OutSocketName) const;
	
};
