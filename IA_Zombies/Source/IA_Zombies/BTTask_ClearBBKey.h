// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_ClearBBKey.generated.h"

/**
 * 
 */
UCLASS()
class IA_ZOMBIES_API UBTTask_ClearBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ClearBBKey();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
