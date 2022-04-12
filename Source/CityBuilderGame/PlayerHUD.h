// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerPawnController.h"
#include "Building.h"
#include "BuildingButton.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBuildingButton* BuildingType1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LimitedNumberOfBuildingsType1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBuildingButton* BuildingType2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LimitedNumberOfBuildingsType2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBuildingButton* BuildingType3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LimitedNumberOfBuildingsType3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBuildingButton* BuildingType4;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LimitedNumberOfBuildingsType4;

	UFUNCTION(BlueprintPure)
	FText GetLimitedNumberOfBuildingsTypeText(int _LimitedNumberOfBuildingsType) const;

protected:
	void NativeConstruct() override;
};
