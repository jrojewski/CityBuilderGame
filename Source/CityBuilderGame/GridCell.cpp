// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCell.h"

// Sets default values
AGridCell::AGridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();
	
	GridCellType = static_cast<EGridCellType>(FMath::RandRange(0, 2));

	switch (GridCellType) {
	case EGridCellType::Green:
		Mesh->SetMaterial(0, GreenGridCellType);
		break;
	case EGridCellType::Grey:
		Mesh->SetMaterial(0, GreyGridCellType);
		break;
	case EGridCellType::Blue:
		Mesh->SetMaterial(0, BlueGridCellType);
		break;
	};
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EGridCellType AGridCell::GetGridCellType() const
{
	return GridCellType;
}

