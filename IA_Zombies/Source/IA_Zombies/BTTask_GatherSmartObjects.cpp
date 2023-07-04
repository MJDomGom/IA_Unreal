#include "BTTask_GatherSmartObjects.h"
#include "IA_SmartObjectBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "IA_BaseInfected_Char.h"

UBTTask_GatherSmartObjects::UBTTask_GatherSmartObjects()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_GatherSmartObjects::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	AIA_BaseInfected_Char* Infected = Controller ? Cast<AIA_BaseInfected_Char>(Controller->GetPawn()) : nullptr;
	if (!Blackboard || !Infected) {
		return EBTNodeResult::Failed;
	}
	AIA_SmartObjectBase* SmartObject = Cast<AIA_SmartObjectBase>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!SmartObject) {
		return EBTNodeResult::Failed;
	}
	Infected->SetCurrentSmartObject(SmartObject);
	return EBTNodeResult::Succeeded;
}
