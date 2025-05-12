// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownShooterPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownShooterCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "BaseMagicCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


void ATopDownShooterPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	PlayerCharacter = Cast<ABaseMagicCharacter>(GetPawn());

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

ATopDownShooterPlayerController::ATopDownShooterPlayerController()
{
}

void ATopDownShooterPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Player Movement
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ATopDownShooterPlayerController::Move);

		//Shooting
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this, &ATopDownShooterPlayerController::FireBullet);
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Started, this, &ATopDownShooterPlayerController::ToggleShooting);
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Completed, this, &ATopDownShooterPlayerController::ToggleShooting);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATopDownShooterPlayerController::ToggleShooting()
{
	PlayerCharacter->ToggleShooting();
}

void ATopDownShooterPlayerController::Move(const FInputActionValue &Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);
	PlayerCharacter->SetMovementRotation(InputVector);

	GetPawn()->AddMovementInput(InputVector, speed, false);
}

void ATopDownShooterPlayerController::FireBullet(const FInputActionValue& Value)
{
	FVector direction = FVector(Value.Get<FVector2D>(), 0);
	PlayerCharacter->ShootBullet(direction);
}

void ATopDownShooterPlayerController::Tick(float DeltaTime)
{

}
