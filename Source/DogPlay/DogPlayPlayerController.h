// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DogPlayPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class DOGPLAY_API ADogPlayPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;


protected:
	virtual void BeginPlay() override;

	
};
