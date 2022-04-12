// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Building.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CityBuilderGameGameModeBase.generated.h"

USTRUCT()
struct FBuildingTypeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> PlaceableActorType;
	UPROPERTY(EditAnywhere)
	int LimitedNumberOfBuildingsType;
};
UCLASS()
class CITYBUILDERGAME_API ACityBuilderGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CheckWinCondition();

	FBuildingTypeData GetBuildingTypeData1();
	FBuildingTypeData GetBuildingTypeData2();
	FBuildingTypeData GetBuildingTypeData3();
	FBuildingTypeData GetBuildingTypeData4();

private:
	UPROPERTY(EditAnywhere)
	FBuildingTypeData BuildingTypeData1;
	UPROPERTY(EditAnywhere)
	FBuildingTypeData BuildingTypeData2;
	UPROPERTY(EditAnywhere)
	FBuildingTypeData BuildingTypeData3;
	UPROPERTY(EditAnywhere)
	FBuildingTypeData BuildingTypeData4;
};
