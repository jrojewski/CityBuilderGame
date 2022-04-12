// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "PlayerPawnController.h"
#include "Kismet/GameplayStatics.h"
#include "CityBuilderGameGameModeBase.h"
#include "CityBuilderGameStateBase.h"

//bool UPlayerHUD::Initialize() {
//	bool Success = Super::Initialize();
//
//	return true;
//}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ACityBuilderGameGameModeBase* CityBuilderGameGameModeBase = Cast<ACityBuilderGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ACityBuilderGameStateBase* CityBuilderGameStateBase = Cast<ACityBuilderGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	
	FBuildingTypeData TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData1();
	BuildingType1->PlaceableActorType = TempBuildingData.PlaceableActorType;
	BuildingType1->_LimitedNumberOfBuildingsType = &CityBuilderGameStateBase->LimitedNumberOfBuildingsType1;

	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData2();
	BuildingType2->PlaceableActorType = TempBuildingData.PlaceableActorType;
	BuildingType2->_LimitedNumberOfBuildingsType = &CityBuilderGameStateBase->LimitedNumberOfBuildingsType2;

	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData3();
	BuildingType3->PlaceableActorType = TempBuildingData.PlaceableActorType;
	BuildingType3->_LimitedNumberOfBuildingsType = &CityBuilderGameStateBase->LimitedNumberOfBuildingsType3;

	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData4();
	BuildingType4->PlaceableActorType = TempBuildingData.PlaceableActorType;
	BuildingType4->_LimitedNumberOfBuildingsType = &CityBuilderGameStateBase->LimitedNumberOfBuildingsType4;
}

FText UPlayerHUD::GetLimitedNumberOfBuildingsTypeText(int _LimitedNumberOfBuildingsType) const
{
	FString LimitedNumberOfBuildingsTypeTextS = FString::FromInt(_LimitedNumberOfBuildingsType);
	FText LimitedNumberOfBuildingsTypeText = FText::FromString(LimitedNumberOfBuildingsTypeTextS);
	return LimitedNumberOfBuildingsTypeText;
}