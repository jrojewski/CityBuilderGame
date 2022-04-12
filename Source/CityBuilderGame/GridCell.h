// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
//#include "Building.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

UENUM()
enum class EGridCellType : int32
{
	Green  UMETA(DisplayName = "Green"),
	Grey   UMETA(DisplayName = "Grey"),
	Blue   UMETA(DisplayName = "Blue"),
};

UCLASS()
class CITYBUILDERGAME_API AGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	AGridCell* NeighbourNorth;
	UPROPERTY(VisibleAnywhere)
	AGridCell* NeighbourEast;
	UPROPERTY(VisibleAnywhere)
	AGridCell* NeighbourSouth;
	UPROPERTY(VisibleAnywhere)
	AGridCell* NeighbourWest;

	UPROPERTY(VisibleAnywhere)
	bool bIsOccupied = false;
	UPROPERTY(VisibleAnywhere)
	class ABuilding* OccupyingBuilding;

	UFUNCTION(BlueprintPure)
	EGridCellType GetGridCellType() const;
private:
	UPROPERTY(EditAnywhere)
	EGridCellType GridCellType;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GreenGridCellType;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GreyGridCellType;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BlueGridCellType;
};
