// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GridCell.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class CITYBUILDERGAME_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetClosestGridCellPosition(FVector_NetQuantize InPosition);
	AGridCell* GetClosestGridCell(FVector_NetQuantize InPosition);

	int NumOfBuildings = 0;
private:
	UPROPERTY(EditDefaultsOnly)
	int GridSize = 50;
	UPROPERTY(EditDefaultsOnly)
	int WorldGridSize = 100;
	UPROPERTY(EditDefaultsOnly)
	TArray<AGridCell*> GridArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGridCell> BP_GridCell;
	UFUNCTION()
	void PopulateGrid();
	UFUNCTION()
	void SetupGridCellNeighbours();
};
