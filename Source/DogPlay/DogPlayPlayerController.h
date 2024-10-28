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
	
public:
	UFUNCTION(Client, Reliable)
	void Client_OnMatchIsOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnMatchIsOver")
	void BPI_OnMatchIsOver(const FText &WinnerName, const int32 &WinnerPoints);
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Bots")
	void DetermineWinningBot(FText &OutName, int32 &OutPoints) const;
	
	
};
