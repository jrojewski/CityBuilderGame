// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "BuildingButton.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API UBuildingButton : public UButton
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ClickOnBuildingButton();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> PlaceableActorType;

	int* _LimitedNumberOfBuildingsType;
};
