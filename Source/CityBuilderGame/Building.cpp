// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	PlacementComponent = CreateDefaultSubobject<UPlacementComponent>(TEXT("PlacementComponent"));
}

UPlacementComponent* ABuilding::GetPlacementComponent() const
{
	return PlacementComponent;
}

float ABuilding::GetPoints()
{
	return Points;
}

float ABuilding::CalculatePointsBasedOnGridCellType(AGridCell* _CurrentGridCell)
{
	float Multiplier = 1.0f;

	EGridCellType GridCellType = _CurrentGridCell->GetGridCellType();

	switch (GridCellType) {
	case EGridCellType::Green:
		Multiplier = GreenGridCellTypeMultiplier;
		break;
	case EGridCellType::Grey:
		Multiplier = GreyGridCellTypeMultiplier;
		break;
	case EGridCellType::Blue:
		Multiplier = BlueGridCellTypeMultiplier;
		break;
	};

	return Multiplier;
}

float ABuilding::CalculatePointsBasedOnNeighbours(AGridCell* _CurrentGridCell)
{
	float CalculatedPoints = 0.0f;

	if (_CurrentGridCell->NeighbourNorth && _CurrentGridCell->NeighbourNorth->OccupyingBuilding)
	{
		CalculatedPoints += CalculatePointsBasedOnNeighboursHelper(_CurrentGridCell->NeighbourNorth->OccupyingBuilding->BuildingType);
	}
	if (_CurrentGridCell->NeighbourSouth && _CurrentGridCell->NeighbourSouth->OccupyingBuilding)
	{
		CalculatedPoints += CalculatePointsBasedOnNeighboursHelper(_CurrentGridCell->NeighbourSouth->OccupyingBuilding->BuildingType);
	}
	if (_CurrentGridCell->NeighbourEast && _CurrentGridCell->NeighbourEast->OccupyingBuilding)
	{
		CalculatedPoints += CalculatePointsBasedOnNeighboursHelper(_CurrentGridCell->NeighbourEast->OccupyingBuilding->BuildingType);
	}
	if (_CurrentGridCell->NeighbourWest && _CurrentGridCell->NeighbourWest->OccupyingBuilding)
	{
		CalculatedPoints += CalculatePointsBasedOnNeighboursHelper(_CurrentGridCell->NeighbourWest->OccupyingBuilding->BuildingType);
	}

	return CalculatedPoints;
}

float ABuilding::CalculatePointsBasedOnNeighboursHelper(EBuildingType NeighbourBuildingType)
{
	float CalculatedPoints = 0.0f;

	EBuildingType _BuildingType = NeighbourBuildingType;
	switch (_BuildingType)
	{
	case EBuildingType::Red:
		CalculatedPoints += NeighbourWithRedPoints;
		break;
	case EBuildingType::Yellow:
		CalculatedPoints += NeighbourWithYellowPoints;
		break;
	case EBuildingType::White:
		CalculatedPoints += NeighbourWithWhitePoints;
		break;
	case EBuildingType::Violet:
		CalculatedPoints += NeighbourWithVioletPoints;
		break;
	};

	return CalculatedPoints;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, Height));
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

