#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GatherSmartObjects.generated.h"


UCLASS()
class IA_ZOMBIES_API UBTTask_GatherSmartObjects : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public: 
	UBTTask_GatherSmartObjects();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
