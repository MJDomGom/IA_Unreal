#include "BTTask_RefreshInitPosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IA_BaseInfected_Char.h"
#include "AIController.h"
#include "IA_SmartObject_Quiet.h"


UBTTask_RefreshInitPosition::UBTTask_RefreshInitPosition() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_RefreshInitPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* Controller = OwnerComp.GetAIOwner();
	AIA_BaseInfected_Char* Infected = Controller ? Cast<AIA_BaseInfected_Char>(Controller->GetPawn()) : nullptr;
	if (!BlackboardComponent || !Infected) {
		return EBTNodeResult::Failed;
	}
	AIA_SmartObject_Quiet* QuietSmartObject = Cast<AIA_SmartObject_Quiet>(Infected->CurrentSmartObject);
	if (!QuietSmartObject) {
		BlackboardComponent->ClearValue("InitPosition");
		return EBTNodeResult::Succeeded;
	}
	if (bHasToLook) {
		BlackboardComponent->SetValueAsVector("PointToLook", QuietSmartObject->PointToLook->GetComponentLocation());
	}
	else {
		BlackboardComponent->SetValueAsVector("InitPosition", QuietSmartObject->GetActorLocation());
	}
	return EBTNodeResult::Succeeded;
}
