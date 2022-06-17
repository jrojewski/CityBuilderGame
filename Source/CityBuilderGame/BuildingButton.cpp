// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingButton.h"

#include "CityBuilderGameStateBase.h"
#include "PlayerPawnController.h"
#include "Kismet/GameplayStatics.h"

void UBuildingButton::ClickOnBuildingButton()
{
	APlayerPawnController* PlayerPawnController = Cast<APlayerPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerPawnController->LimitedNumberOfBuildingsType = _LimitedNumberOfBuildingsType;

	if (*_LimitedNumberOfBuildingsType == 0) return;

	PlayerPawnController->SetPlaceableActorType(PlaceableActorType);
	PlayerPawnController->SetPlacementModeEnabled(true);

}
