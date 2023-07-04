#include "BTTask_ResetSmartObject.h"
#include "IA_BaseInfected_Char.h"
#include "AIController.h"

UBTTask_ResetSmartObject::UBTTask_ResetSmartObject() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ResetSmartObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	AIA_BaseInfected_Char* BaseInfected = Controller ? Cast<AIA_BaseInfected_Char>(Controller->GetPawn()) : nullptr;
	if (!BaseInfected) {
		return EBTNodeResult::Failed;
	}
	BaseInfected->ResetSmartObject();
	return EBTNodeResult::Succeeded;
}
