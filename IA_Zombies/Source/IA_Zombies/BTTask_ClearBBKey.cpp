// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_ClearBBKey.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBBKey::UBTTask_ClearBBKey() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ClearBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackBoardComponent) {
		return EBTNodeResult::Failed;
	}
	BlackBoardComponent->ClearValue(BlackboardKey.GetSelectedKeyID());
	return EBTNodeResult::Succeeded;
}
