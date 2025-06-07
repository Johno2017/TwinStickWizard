// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepletedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// Current health
	UPROPERTY()
	float Health;

	// Max health
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float MaxHealth;

public:
	UHealthComponent();

	FOnHealthDepletedSignature OnHealthDepleted;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float DeltaHealth);
};
