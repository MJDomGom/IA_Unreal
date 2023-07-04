#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "BTTask_GetPathPoint.generated.h"


UCLASS()
class IA_ZOMBIES_API UBTTask_GetPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		bool bIsHearing = false;
	UBTTask_GetPathPoint();
private:
	int32 index = 0;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
