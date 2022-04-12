// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlacementComponent.h"
#include "GridCell.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UENUM()
enum class EBuildingType : int32
{
	Red      UMETA(DisplayName = "Red"),
	Violet   UMETA(DisplayName = "Violet"),
	White    UMETA(DisplayName = "White"),
	Yellow   UMETA(DisplayName = "Yellow"),
};

UCLASS()
class CITYBUILDERGAME_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	UFUNCTION(BlueprintCallable)
	UPlacementComponent* GetPlacementComponent() const;

	UFUNCTION(BlueprintCallable)
	float GetPoints();

	virtual float CalculatePointsBasedOnGridCellType(AGridCell* _CurrentGridCell);
	UPROPERTY(EditDefaultsOnly)
	float GreenGridCellTypeMultiplier = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float GreyGridCellTypeMultiplier = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float BlueGridCellTypeMultiplier = 1.0f;

	virtual float CalculatePointsBasedOnNeighbours(AGridCell* _CurrentGridCell);
	float CalculatePointsBasedOnNeighboursHelper(EBuildingType NeighbourBuildingType);
	UPROPERTY(EditDefaultsOnly)
	EBuildingType BuildingType;
	UPROPERTY(EditDefaultsOnly)
	float NeighbourWithRedPoints = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float NeighbourWithYellowPoints = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float NeighbourWithWhitePoints = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float NeighbourWithVioletPoints = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	float Height = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	UPlacementComponent* PlacementComponent;
	UPROPERTY(EditDefaultsOnly)
	float Points = 1.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
