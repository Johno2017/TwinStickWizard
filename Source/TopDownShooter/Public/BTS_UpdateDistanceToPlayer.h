// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_UpdateDistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTS_UpdateDistanceToPlayer : public UBTService
{
	GENERATED_BODY()

	UBTS_UpdateDistanceToPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = BlackBoard)
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, Category = BlackBoard)
	FBlackboardKeySelector Player;	

	UPROPERTY(EditAnywhere, Category = BlackBoard)
	FBlackboardKeySelector DistanceToPlayer;
};
