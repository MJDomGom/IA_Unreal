#include "BTTask_GetPathPoint.h"
#include "IA_BaseInfected_Char.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIController.h"
#include "IA_SmartObjectPatrol.h"

UBTTask_GetPathPoint::UBTTask_GetPathPoint() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_GetPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();
	AIA_BaseInfected_Char* MyInfected = MyController ? Cast<AIA_BaseInfected_Char>(MyController->GetPawn()) : nullptr;

	if (!MyInfected || !BlackboardComponent) {
		return EBTNodeResult::Failed;
	}
	AIA_SmartObjectPatrol* SmartObjectPatrol = Cast<AIA_SmartObjectPatrol>(MyInfected->CurrentSmartObject);
	const TArray<FVector>& SplinePoints = SmartObjectPatrol ? SmartObjectPatrol->GetSplinePoints() : TArray<FVector>();

	if (SplinePoints.IsEmpty()) {
		return EBTNodeResult::Succeeded;
	}

	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(GetSelectedBlackboardKey(), SplinePoints[index]);
	if (index < SplinePoints.Num() - 1) {
		index++;
		return EBTNodeResult::Succeeded;
	}
	index = 0;
	return EBTNodeResult::Succeeded;
}
