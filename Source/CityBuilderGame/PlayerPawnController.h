// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GridCell.h"
#include "Building.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPawnController.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDERGAME_API APlayerPawnController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerPawnController();

	void CallHUD();
	void PrepareGameHUD();
	void CallEndGameBoard();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void SetPlaceableActorType(TSubclassOf<ABuilding> NewBuildingType);
	void SetPlacementModeEnabled(bool bIsEnabled);
	void UpdatePlacement();
	void SpawnBuilding();

	UPROPERTY()
	ABuilding* PlaceableActor = nullptr;

	int* LimitedNumberOfBuildingsType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	bool bPlacementModeEnabled = false;
	//UPROPERTY()
	//AActor* PlaceableActor;
	UPROPERTY(EditDefaultsOnly)
	UClass* PlaceableActorType = ABuilding::StaticClass();
	UPROPERTY()
	AGridCell* CurrentGridCell;

	class UStartGameBoard* StartGameBoard;
	class UPlayerHUD* PlayerHUD;
	class UEndGameBoard* EndGameBoard;
};
