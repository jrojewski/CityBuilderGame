// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameBoard.h"

#include "PlayerPawnController.h"
#include "Kismet/GameplayStatics.h"

void UStartGameBoard::StartGame()
{
	Cast<APlayerPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->PrepareGameHUD();
}
