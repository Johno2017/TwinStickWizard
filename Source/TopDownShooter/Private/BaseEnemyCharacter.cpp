// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"
#include "HealthComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter() {
	if (HealthComponent) {
		HealthComponent->SetHealth(HP);
		HealthComponent->SetMaxHealth(HP);
	}
}