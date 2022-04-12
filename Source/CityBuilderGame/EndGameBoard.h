// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameBoard.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API UEndGameBoard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FinalScore;

protected:
	void NativeConstruct() override;
};
