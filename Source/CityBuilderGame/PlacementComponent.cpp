// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementComponent.h"

#include "GridManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawnController.h"
#include "Building.h"

// Sets default values for this component's properties
UPlacementComponent::UPlacementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FoundValidPlacementMaterial(TEXT("/Game/Materials/Buildings/M_Basic_Wall_Valid.M_Basic_Wall_Valid"));
	if (FoundValidPlacementMaterial.Succeeded())
	{
		ValidPlacementMaterial = FoundValidPlacementMaterial.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FoundInValidPlacementMaterial(TEXT("/Game/Materials/Buildings/M_Basic_Wall_Invalid.M_Basic_Wall_Invalid"));
	if (FoundInValidPlacementMaterial.Succeeded())
	{
		InValidPlacementMaterial = FoundInValidPlacementMaterial.Object;
	}
}


// Called when the game starts
void UPlacementComponent::BeginPlay()
{
	Super::BeginPlay();


	//GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UPlacementComponent::UpdateState);
	//GetOwner()->OnActorEndOverlap.AddDynamic(this, &UPlacementComponent::UpdateState);

	//UpdateStateLogic();
}


// Called every frame
void UPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlacementComponent::UpdateState(AActor* OverlappedActor, AActor* OtherActor)
{
	//UpdateStateLogic();
}

void UPlacementComponent::UpdateStateLogic(AGridCell* CurrentGridCell)
{
	//TSet<AActor*> CurrentOverlappingActors; For tests put in public
	GetOwner()->GetOverlappingActors(CurrentOverlappingActors);

	AGridManager* CurrentGridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass()));
	//AGridCell* CurrentGridCell = CurrentGridManager->GetClosestGridCell(Cast<APlayerPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->PlaceableActor->GetActorLocation());

	if (CurrentGridManager->NumOfBuildings > 0)
	{
		bool bIsNeighbourOccupied = false;

		if (CurrentGridCell->NeighbourEast != nullptr)
		{
			if (CurrentGridCell->NeighbourEast->bIsOccupied == true)
			{
				bIsNeighbourOccupied = true;
			}
		}

		if (CurrentGridCell->NeighbourWest != nullptr)
		{
			if (CurrentGridCell->NeighbourWest->bIsOccupied == true)
			{
				bIsNeighbourOccupied = true;
			}
		}

		if (CurrentGridCell->NeighbourNorth != nullptr)
		{
			if (CurrentGridCell->NeighbourNorth->bIsOccupied == true)
			{
				bIsNeighbourOccupied = true;
			}
		}

		if (CurrentGridCell->NeighbourSouth != nullptr)
		{
			if (CurrentGridCell->NeighbourSouth->bIsOccupied == true)
			{
				bIsNeighbourOccupied = true;
			}
		}

		if ((CurrentGridCell->GetGridCellType() != EGridCellType::Blue) && (CurrentGridCell->bIsOccupied == false) && (bIsNeighbourOccupied == true)) //&& (CurrentGridCell->NeighbourEast->bIsOccupied == true || CurrentGridCell->NeighbourWest->bIsOccupied == true || CurrentGridCell->NeighbourNorth->bIsOccupied == true || CurrentGridCell->NeighbourSouth->bIsOccupied == true))
		{
			bIsPlacementValid = true;
			TArray<UActorComponent*> StaticMeshes = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());

			for (auto x : StaticMeshes)
			{
				Cast<UStaticMeshComponent>(x)->SetMaterial(0, ValidPlacementMaterial);
			}
		}
		else
		{
			bIsPlacementValid = false;
			TArray<UActorComponent*> StaticMeshes = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());

			for (auto x : StaticMeshes)
			{
				Cast<UStaticMeshComponent>(x)->SetMaterial(0, InValidPlacementMaterial);
			}
		}
	}
	else
	{
		if ((CurrentGridCell->GetGridCellType() != EGridCellType::Blue) && (CurrentGridCell->bIsOccupied == false))
		{
			bIsPlacementValid = true;
				TArray<UActorComponent*> StaticMeshes = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());

				for (auto x : StaticMeshes)
				{
					Cast<UStaticMeshComponent>(x)->SetMaterial(0, ValidPlacementMaterial);
				}
		}
		else
	    {
			bIsPlacementValid = false;
			TArray<UActorComponent*> StaticMeshes = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());

			for (auto x : StaticMeshes)
			{
				Cast<UStaticMeshComponent>(x)->SetMaterial(0, InValidPlacementMaterial);
			}
		} 
	}
}