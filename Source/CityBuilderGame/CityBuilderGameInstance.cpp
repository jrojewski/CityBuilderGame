// Fill out your copyright notice in the Description page of Project Settings.


#include "CityBuilderGameInstance.h"

#include "StartGameBoard.h"
#include "PlayerHUD.h"
#include "EndGameBoard.h"

UCityBuilderGameInstance::UCityBuilderGameInstance(const FObjectInitializer& ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> StartGameBoardBPClass(TEXT("/Game/Blueprints/WBP_StartGameBoard"));
	if (StartGameBoardBPClass.Class == nullptr) return;
	StartGameBoardClass = StartGameBoardBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDBPClass(TEXT("/Game/Blueprints/WBP_PlayerHUD"));
	if (PlayerHUDBPClass.Class == nullptr) return;
	PlayerHUDClass = PlayerHUDBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Blueprints/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class == nullptr) return;
	InGameMenuClass = InGameMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> EndGameBoardBPClass(TEXT("/Game/Blueprints/WBP_EndGameBoard"));
	if (EndGameBoardBPClass.Class == nullptr) return;
	EndGameBoardClass = EndGameBoardBPClass.Class;
}