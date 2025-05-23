// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMagicCharacter.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API ABaseMagicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMagicCharacter();

	//Set Defaults for rotators
	FRotator ShootRot = FRotator::ZeroRotator;
	FRotator MovementRot = FRotator::ZeroRotator;

	void ToggleShooting();
	void SetMovementRotation(FVector RotValue);
	AActor* ShootBullet(FVector Direction);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float HP = 50;

	UPROPERTY(BlueprintReadOnly)
	bool uIsShooting = false;

	UPROPERTY(EditAnywhere)
	float TimeBetweenFires = 0.2f;

	bool uCanFire = true;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseBullet> BulletToSpawn;

	UPROPERTY(EditAnywhere)
	UChildActorComponent* Weapon;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnLocation;

	UFUNCTION(BlueprintPure)
	FVector CalculateMovementBlending();

	void SetCanFire(bool Value);

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	);

};
