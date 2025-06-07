// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void UHealthComponent::UpdateHealth(float DeltaHealth)
{
	Health += DeltaHealth;
	//Clamp the health to avoid values less than 0 and bigger than MaxHealth
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if (Health == 0.0f)
	{
		OnHealthDepleted.Broadcast();
	}
}


