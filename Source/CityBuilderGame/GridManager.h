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

private:
	UPROPERTY(EditDefaultsOnly)
	int GridSize = 10;
	UPROPERTY(EditDefaultsOnly)
	int WorldGridSize = 1000;
	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> GridArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGridCell> BP_GridCell;
	UFUNCTION()
	void PopulateGrid();
};
