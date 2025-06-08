// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMagicCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ABaseEnemyCharacter : public ABaseMagicCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BTAsset;
	
};
