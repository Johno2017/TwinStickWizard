// Fill out your copyright notice in the Description page of Project Settings.


#include "BBT_EnemyBasicShoot.h"
#include "BaseEnemyCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBBT_EnemyBasicShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(controller->GetPawn());

	Enemy->Fire(controller->GetPawn()->GetActorForwardVector());

	return EBTNodeResult::Type();
}
