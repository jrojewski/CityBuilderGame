// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameBoard.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API UStartGameBoard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartButton;

	UFUNCTION(BlueprintCallable)
	void StartGame();
};
