// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CITYBUILDERGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement;

	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 1.0f;
	UFUNCTION()
	void RotateCamera(float AxisValue);
	UPROPERTY(EditDefaultsOnly)
	float CameraRotateSpeed = 1.0f;
	UFUNCTION()
	void ZoomCamera(float AxisValue);
	UPROPERTY(EditDefaultsOnly)
	float ZoomSpeed = 50.0f;
	UPROPERTY(EditDefaultsOnly)
	float NewTargetArmLength;
	UPROPERTY(EditDefaultsOnly)
	float ZoomInterpSpeed = 15.0f;
	UPROPERTY(EditDefaultsOnly)
	float MinSpringArmLength = 150.0f;
	UPROPERTY(EditDefaultsOnly)
	float MaxSpringArmLength = 750.0f;
};
