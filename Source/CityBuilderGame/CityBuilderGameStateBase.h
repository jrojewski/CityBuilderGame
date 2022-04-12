// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CityBuilderGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API ACityBuilderGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int LimitedNumberOfBuildingsType1;
	UFUNCTION(BlueprintPure)
	int GetLimitedNumberOfBuildingsType1() const;
	int LimitedNumberOfBuildingsType2;
	UFUNCTION(BlueprintPure)
	int GetLimitedNumberOfBuildingsType2() const;
	int LimitedNumberOfBuildingsType3;
	UFUNCTION(BlueprintPure)
	int GetLimitedNumberOfBuildingsType3() const;
	int LimitedNumberOfBuildingsType4;
	UFUNCTION(BlueprintPure)
	int GetLimitedNumberOfBuildingsType4() const;

protected:
	void BeginPlay() override;
};
