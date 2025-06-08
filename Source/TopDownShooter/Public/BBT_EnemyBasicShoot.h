// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BBT_EnemyBasicShoot.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBBT_EnemyBasicShoot : public UBTTaskNode
{
	GENERATED_BODY()


	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
