// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

#include "GridCell.h"
#include "Math/UnrealMathUtility.h"

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
	SetupGridCellNeighbours();
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AGridManager::GetClosestGridCellPosition(FVector_NetQuantize InPosition)
{
	FVector ClosestPosition;
	float ClosestDistance;

	ClosestPosition = GridArray[0]->GetActorLocation();

	ClosestDistance = FVector::Distance(InPosition, ClosestPosition);

	for (auto GridCell : GridArray)
	{
		if (FVector::Distance(GridCell->GetActorLocation(), InPosition) < ClosestDistance)
		{
			ClosestPosition = GridCell->GetActorLocation();
			ClosestDistance = FVector::Distance(GridCell->GetActorLocation(), InPosition);
		}
	}

	return ClosestPosition;
}

AGridCell* AGridManager::GetClosestGridCell(FVector_NetQuantize InPosition)
{
	float ClosestDistance;
	int ArrayIndex = 0;

	ClosestDistance = FVector::Distance(InPosition, GridArray[0]->GetActorLocation());

	for (int i = 0; i < GridArray.Num(); i++)
	{
		if (FVector::Distance(GridArray[i]->GetActorLocation(), InPosition) < ClosestDistance)
		{
			ClosestDistance = FVector::Distance(GridArray[i]->GetActorLocation(), InPosition);
			ArrayIndex = i;
		}
	}



	return GridArray[ArrayIndex];
}

void AGridManager::PopulateGrid()
{
	GridArray.Empty();

	float WorldOffset = ((GridSize * WorldGridSize) * 0.5f) - (WorldGridSize * 0.5f);

	for (int y = 0; y < GridSize; y++)
	{
		for (int x = 0; x < GridSize; x++)
		{
			//FMath::RandRange(1, NumOfGridCellTypes)
			GridArray.Add(GetWorld()->SpawnActor<AGridCell>(BP_GridCell, FVector(((x * WorldGridSize) - WorldOffset), ((y * WorldGridSize) - WorldOffset), 0.0f), FRotator(0.0f, 0.0f, 0.0f)));
		}
	}
}

void AGridManager::SetupGridCellNeighbours()
{
	for (int i = 0; i < GridArray.Num(); i++)
	{
		//East Neighbour
		if ((i - GridSize) >= 0)
		{
			GridArray[i]->NeighbourEast = GridArray[i - GridSize];
		}
		//West Neighbour
		if ((i + GridSize) < GridArray.Num())
		{
			GridArray[i]->NeighbourWest = GridArray[i + GridSize];
		}
		//North Neighbour
		if ((i % GridSize) != 0)
		{
			GridArray[i]->NeighbourNorth = GridArray[i - 1];
		}
		//South Neighbour
		if (((i + 1) % GridSize) != 0)
		{
			GridArray[i]->NeighbourSouth = GridArray[i + 1];
		}
	}
}

