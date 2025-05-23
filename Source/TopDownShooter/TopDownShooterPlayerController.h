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

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere)
	float speed;

	void Move(const FInputActionValue& Value);

	void FireBullet(const FInputActionValue& Value);

	void ToggleShooting();

	class ABaseMagicCharacter* PlayerCharacter;

	virtual void Tick(float DeltaTime) override;


};


