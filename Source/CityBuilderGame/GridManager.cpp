// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

#include "GridCell.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	PopulateGrid();
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridManager::PopulateGrid()
{
	GridArray.Empty();

	float WorldOffset = ((GridSize * WorldGridSize) * 0.5f) - (WorldGridSize * 0.5f);

	for (int y = 0; y < GridSize; y++)
	{
		for (int x = 0; x < GridSize; x++)
		{
			GridArray.Add(GetWorld()->SpawnActor<AGridCell>(BP_GridCell, FVector(((x * WorldGridSize) - WorldOffset), ((y * WorldGridSize) - WorldOffset), 0.0f),FRotator(0.0f,0.0f,0.0f)));
		}
	}
}

