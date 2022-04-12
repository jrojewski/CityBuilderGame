// Copyright Epic Games, Inc. All Rights Reserved.


#include "CityBuilderGameGameModeBase.h"

#include "CityBuilderGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawnController.h"

void ACityBuilderGameGameModeBase::CheckWinCondition()
{
	ACityBuilderGameStateBase* CityBuilderGameStateBase = Cast<ACityBuilderGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	int WinCheck = 0;
	WinCheck += CityBuilderGameStateBase->GetLimitedNumberOfBuildingsType1();
	WinCheck += CityBuilderGameStateBase->GetLimitedNumberOfBuildingsType2();
	WinCheck += CityBuilderGameStateBase->GetLimitedNumberOfBuildingsType3();
	WinCheck += CityBuilderGameStateBase->GetLimitedNumberOfBuildingsType4();

	if (WinCheck == 0)
	{
		Cast<APlayerPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->CallEndGameBoard();
	}
}

FBuildingTypeData ACityBuilderGameGameModeBase::GetBuildingTypeData1()
{
	return BuildingTypeData1;
}

FBuildingTypeData ACityBuilderGameGameModeBase::GetBuildingTypeData2()
{
	return BuildingTypeData2;
}

FBuildingTypeData ACityBuilderGameGameModeBase::GetBuildingTypeData3()
{
	return BuildingTypeData3;
}

FBuildingTypeData ACityBuilderGameGameModeBase::GetBuildingTypeData4()
{
	return BuildingTypeData4;
}
