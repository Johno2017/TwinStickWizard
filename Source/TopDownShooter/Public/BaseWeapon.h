// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	void WeaponShoot();

	ACharacter* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerPointer(ACharacter* PlayerPtr);

};
