#include "BTTask_IdleBreaker.h"
#include "AIController.h"
#include "IA_BaseInfected_Char.h"
#include <Kismet/KismetMathLibrary.h>
#include "Animation/AnimMontage.h"


UBTTask_IdleBreaker::UBTTask_IdleBreaker()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_IdleBreaker::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Animations.IsEmpty()) {
		return EBTNodeResult::Succeeded;
	}

	AAIController* Controller = OwnerComp.GetAIOwner();
	AIA_BaseInfected_Char* Infected = Controller ? Cast<AIA_BaseInfected_Char>(Controller->GetPawn()) : nullptr;
	MyOwnerComp = &OwnerComp;

	if (!Infected) {
		return EBTNodeResult::Failed;
	}
	int32 RandomIndex = UKismetMathLibrary::RandomInteger(Animations.Num());
	UAnimMontage* MontageToPlay = Animations[RandomIndex];
	if (!MontageToPlay) {
		return EBTNodeResult::Failed;
	}
	CachedSkelMesh = Infected->GetMesh();
	CachedSkelMesh->PlayAnimation(MontageToPlay,false);
	const float FinishDelay = MontageToPlay->GetPlayLength();
	GetWorld()->GetTimerManager().SetTimer(AnimTimer,this,&UBTTask_IdleBreaker::OnTimerFinished,FinishDelay,false );
	return EBTNodeResult::InProgress;
}

void UBTTask_IdleBreaker::OnTimerFinished()
{
	CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
}
