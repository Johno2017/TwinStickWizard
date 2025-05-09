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

void ATopDownShooterPlayerController::Move(const FInputActionValue &Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector InputVector = FVector(MovementVector, 0);
	MovementRot = InputVector.Rotation();

	GetPawn()->AddMovementInput(InputVector, speed, false);
}

void ATopDownShooterPlayerController::FireBullet(const FInputActionValue& Value)
{
	if (PlayerCharacter) 
	{
		FVector direction = FVector(Value.Get<FVector2D>(), 0);
		ShootRot = direction.Rotation();

		if (CanFire) {
			PlayerCharacter->ShootBullet();
			CanFire = false;

			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATopDownShooterPlayerController::SetCanFire, true);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimeBetweenFires, false);
		}
		
	}
}

void ATopDownShooterPlayerController::SetCanFire(bool Value)
{
	CanFire = Value;
}

void ATopDownShooterPlayerController::ToggleShooting()
{
	IsShooting = !IsShooting;
}

FVector ATopDownShooterPlayerController::CalculateMovementBlending()
{
	FVector movement = MovementRot.Vector();
	FVector shooting = ShootRot.Vector();

	float DotProd = FVector::DotProduct(movement, shooting);

	FVector BlendVector = movement - shooting * DotProd;

	FVector OutputVector = FVector(DotProd, BlendVector.Length(), 0);

	return OutputVector * 100;
}

void ATopDownShooterPlayerController::Tick(float DeltaTime)
{
	FRotator currentOrientation;
	if (IsShooting) 
	{
		currentOrientation = ShootRot;
	}
	else 
	{
		currentOrientation = MovementRot;
	}

	PlayerCharacter->SetActorRotation(currentOrientation);
}
