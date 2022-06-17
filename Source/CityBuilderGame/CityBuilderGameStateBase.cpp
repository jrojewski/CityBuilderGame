// Fill out your copyright notice in the Description page of Project Settings.


#include "CityBuilderGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "CityBuilderGameGameModeBase.h"

void ACityBuilderGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	ACityBuilderGameGameModeBase* CityBuilderGameGameModeBase = Cast<ACityBuilderGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	FBuildingTypeData TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData1();
	LimitedNumberOfBuildingsType1 = TempBuildingData.LimitedNumberOfBuildingsType;
	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData2();
	LimitedNumberOfBuildingsType2 = TempBuildingData.LimitedNumberOfBuildingsType;
	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData3();
	LimitedNumberOfBuildingsType3 = TempBuildingData.LimitedNumberOfBuildingsType;
	TempBuildingData = CityBuilderGameGameModeBase->GetBuildingTypeData4();
	LimitedNumberOfBuildingsType4 = TempBuildingData.LimitedNumberOfBuildingsType;
}

int ACityBuilderGameStateBase::GetLimitedNumberOfBuildingsType1() const
{
	return LimitedNumberOfBuildingsType1;
}

int ACityBuilderGameStateBase::GetLimitedNumberOfBuildingsType2() const
{
	return LimitedNumberOfBuildingsType2;
}

int ACityBuilderGameStateBase::GetLimitedNumberOfBuildingsType3() const
{
	return LimitedNumberOfBuildingsType3;
}

int ACityBuilderGameStateBase::GetLimitedNumberOfBuildingsType4() const
{
	return LimitedNumberOfBuildingsType4;
}