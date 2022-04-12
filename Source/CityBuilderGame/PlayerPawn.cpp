// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "PlayerPawnController.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	Cast<APlayerPawnController>(GetController())->CallHUD();
	
	SpringArm->TargetArmLength = MaxSpringArmLength / 2.0f;
	NewTargetArmLength = MaxSpringArmLength / 2.0f;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &APlayerPawn::RotateCamera);
	PlayerInputComponent->BindAxis(TEXT("ZoomCamera"), this, &APlayerPawn::ZoomCamera);
}

FText APlayerPawn::GetScoreText() const
{
	FString ScoreS = FString::SanitizeFloat(Score);
	FText ScoreText = FText::FromString(ScoreS);
	return ScoreText;
}

void APlayerPawn::SetScore(float _points)
{
	Score = Score + _points;
	return;
}

void APlayerPawn::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MovementSpeed);
}

void APlayerPawn::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * MovementSpeed);
}

void APlayerPawn::RotateCamera(float AxisValue)
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + (AxisValue * CameraRotateSpeed), CurrentRotation.Roll);
	SetActorRotation(NewRotation);
}

void APlayerPawn::ZoomCamera(float AxisValue)
{
	NewTargetArmLength = FMath::Clamp(AxisValue * ZoomSpeed + NewTargetArmLength, MinSpringArmLength, MaxSpringArmLength);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, NewTargetArmLength, GetWorld()->GetDeltaSeconds(), ZoomInterpSpeed);
}
