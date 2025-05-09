// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TopDownShooterPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATopDownShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownShooterPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MovementInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireInput;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere)
	float speed;

	void Move(const FInputActionValue& Value);

	void FireBullet(const FInputActionValue& Value);

	void SetCanFire(bool Value);

	class ABaseMagicCharacter* PlayerCharacter;

	bool CanFire = true;

	UPROPERTY(BlueprintReadOnly)
	bool IsShooting;

	void ToggleShooting();

	UFUNCTION(BlueprintPure)
	FVector CalculateMovementBlending();

	FRotator ShootRot;
	FRotator MovementRot;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float TimeBetweenFires = 0.2f;


};


