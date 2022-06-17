// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"

#include "PlacementComponent.h"
#include "GridManager.h"
#include "Kismet/GameplayStatics.h"
#include "CityBuilderGameInstance.h"
#include "StartGameBoard.h"
#include "PlayerHUD.h"
#include "EndGameBoard.h"
#include "PlayerPawn.h"
#include "Building.h"
#include "CityBuilderGameGameModeBase.h"
#include "Particles/ParticleSystemComponent.h"

APlayerPawnController::APlayerPawnController() {
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void APlayerPawnController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	this->SetInputMode(InputModeGameAndUI);
}

void APlayerPawnController::CallHUD() {
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	UCityBuilderGameInstance* CityBuilderGameInstance = Cast<UCityBuilderGameInstance>(UGameplayStatics::GetGameInstance(World));
	if (CityBuilderGameInstance == nullptr) return;

	StartGameBoard = CreateWidget<UStartGameBoard>(this, CityBuilderGameInstance->StartGameBoardClass);
	if (StartGameBoard == nullptr) return;
	StartGameBoard->AddToViewport();

	PlayerHUD = CreateWidget<UPlayerHUD>(this, CityBuilderGameInstance->PlayerHUDClass);
	if (PlayerHUD == nullptr) return;
	PlayerHUD->AddToViewport();
	PlayerHUD->SetVisibility(ESlateVisibility::Hidden);

	InGameMenu = CreateWidget<UUserWidget>(this, CityBuilderGameInstance->InGameMenuClass);
	if (InGameMenu == nullptr) return;
	InGameMenu->AddToViewport();
	InGameMenu->SetVisibility(ESlateVisibility::Hidden);

	EndGameBoard = CreateWidget<UEndGameBoard>(this, CityBuilderGameInstance->EndGameBoardClass);
	if (EndGameBoard == nullptr) return;
	EndGameBoard->AddToViewport();
	EndGameBoard->SetVisibility(ESlateVisibility::Hidden);
}

void APlayerPawnController::PrepareGameHUD()
{
	StartGameBoard->SetVisibility(ESlateVisibility::Hidden);
	PlayerHUD->SetVisibility(ESlateVisibility::Visible);
}

void APlayerPawnController::CallEndGameBoard()
{
	PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
	EndGameBoard->SetVisibility(ESlateVisibility::Visible);
	bInGameMenuAvailable = false;
}

void APlayerPawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlacementModeEnabled)
	{
		UpdatePlacement();
	}
}

void APlayerPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LMB", EInputEvent::IE_Pressed, this, &APlayerPawnController::SpawnBuilding);
}

void APlayerPawnController::SetPlaceableActorType(TSubclassOf<ABuilding> NewBuildingType)
{
	PlaceableActorType = NewBuildingType;
}

void APlayerPawnController::SetPlacementModeEnabled(bool bIsEnabled)
{
	if (bPlacementModeEnabled == bIsEnabled)
	{
		if (PlaceableActor != nullptr)
		{
			PlaceableActor->Destroy();
		}
	}
	else
	{
		bPlacementModeEnabled = bIsEnabled;
	}


	if (bIsEnabled)
	{
		FActorSpawnParameters BuildingSpawnParams;
		BuildingSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PlaceableActor = GetWorld()->SpawnActor<ABuilding>(PlaceableActorType,FVector(0.0f, 0.0f, -1000000.0f), FRotator(0.0f, 0.0f, 0.0f), BuildingSpawnParams);
	}
	else
	{
		PlaceableActor->Destroy();
	}
}

void APlayerPawnController::UpdatePlacement()
{
	FVector WorldLocation;
	FVector Direction;
	DeprojectMousePositionToWorld(WorldLocation, Direction);
	FHitResult Hit;
	Direction = WorldLocation + Direction * 10000;
	GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, Direction, ECollisionChannel::ECC_GameTraceChannel1);

	if (Hit.bBlockingHit)
	{
		AGridManager* CurrentGridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass()));
		if (CurrentGridManager == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrentGridManager == nullptr"))
			return;
		}
		CurrentGridCell = CurrentGridManager->GetClosestGridCell(Hit.Location);
		PlaceableActor->SetActorLocation(FVector(CurrentGridCell->GetActorLocation().X, CurrentGridCell->GetActorLocation().Y, CurrentGridCell->GetActorLocation().Z + 20.0f));
		PlaceableActor->GetPlacementComponent()->UpdateStateLogic(CurrentGridCell);
	}
}

void APlayerPawnController::SpawnBuilding()
{
	if (bPlacementModeEnabled)
	{
		if (!PlaceableActor)
		{
			return;
		}

		if (Cast<UPlacementComponent>(PlaceableActor->GetComponentByClass(UPlacementComponent::StaticClass()))->bIsPlacementValid)
		{
			*LimitedNumberOfBuildingsType = *LimitedNumberOfBuildingsType - 1;

			FActorSpawnParameters BuildingSpawnParams;
			BuildingSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ABuilding* TempBuilding = GetWorld()->SpawnActor<ABuilding>(PlaceableActorType, PlaceableActor->GetActorTransform().GetLocation(), FRotator(0.0f, 0.0f, 0.0f), BuildingSpawnParams);
			SetPlacementModeEnabled(false);

			AGridManager* CurrentGridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass()));

			CurrentGridCell->bIsOccupied = true;
			CurrentGridCell->OccupyingBuilding = TempBuilding;
			CurrentGridManager->NumOfBuildings++;

			float CalculatedPoints = PlaceableActor->GetPoints();
			CalculatedPoints = CalculatedPoints * PlaceableActor->CalculatePointsBasedOnGridCellType(CurrentGridCell);
			CalculatedPoints = CalculatedPoints + PlaceableActor->CalculatePointsBasedOnNeighbours(CurrentGridCell);

			Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->SetScore(CalculatedPoints);

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PlaceableActor->ConstructionSound, PlaceableActor->GetActorTransform().GetLocation());
			UParticleSystemComponent* SmokeParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PlaceableActor->ConstructionParticles, PlaceableActor->GetActorTransform().GetLocation(), FRotator::ZeroRotator, FVector(1.5f, 0.5f, 0.5f));
			ConstructionEffectsDelegate.BindUFunction(this, FName("DeactivateConstructionEffects"), SmokeParticleSystemComponent);
			GetWorldTimerManager().SetTimer(ConstructionEffectsTimer, ConstructionEffectsDelegate, 0.05f, false);

			Cast<ACityBuilderGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->CheckWinCondition();
		}
		else 
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PlaceableActor->ErrorSound, PlaceableActor->GetActorTransform().GetLocation());
		}
	}
}

void APlayerPawnController::DeactivateConstructionEffects(UParticleSystemComponent* _SmokeUParticleSystemComponent)
{
	_SmokeUParticleSystemComponent->DeactivateSystem();
}