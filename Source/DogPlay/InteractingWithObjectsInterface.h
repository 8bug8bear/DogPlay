// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractingWithObjectsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractingWithObjectsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DOGPLAY_API IInteractingWithObjectsInterface
{
	GENERATED_BODY()

public:
	/*
	 * The main parameters can be taken from the local instance of the object.
	 * But these two parameters change too quickly, so to match the states when interacting with the object, they should be passed manually
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	void UseObject(FVector Location, FVector Direction);
	
	// To return the object to working capacity if it is deprived of it for some reason
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	void RechargeObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	void SetUniqueItemID(uint8 InNewID);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	uint8 GetUniqueItemID() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inteructuin")
	void SetObjectVisibility(bool InNewVisibility);
	
};
