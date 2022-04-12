// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlacementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYBUILDERGAME_API UPlacementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlacementComponent();

	UFUNCTION()
	void UpdateState(AActor* OverlappedActor, AActor* OtherActor);

	TSet<AActor*> CurrentOverlappingActors;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	bool bIsPlacementValid = true;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* ValidPlacementMaterial;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* InValidPlacementMaterial;

	void UpdateStateLogic(class AGridCell* CurrentGridCell);
private:
	//void UpdateStateLogic();
};
