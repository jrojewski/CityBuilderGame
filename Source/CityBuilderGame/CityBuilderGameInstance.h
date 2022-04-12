// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CityBuilderGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API UCityBuilderGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCityBuilderGameInstance(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<class UStartGameBoard> StartGameBoardClass;
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;
	TSubclassOf<class UEndGameBoard> EndGameBoardClass;
};
