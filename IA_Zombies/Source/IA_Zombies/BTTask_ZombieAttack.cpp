#include "BTTask_ZombieAttack.h"
#include "IA_BaseInfected_Char.h"
#include "AIController.h"
#include <Kismet/KismetMathLibrary.h>


UBTTask_ZombieAttack::UBTTask_ZombieAttack()
{
	bCreateNodeInstance = true;

}

EBTNodeResult::Type UBTTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	MyInfected = Controller ? Cast<AIA_BaseInfected_Char>(Controller->GetPawn()) : nullptr;
	if (!MyInfected) {
		return EBTNodeResult::Failed;
	}
	MyOwnerComp = &OwnerComp;
	ComboNumber = UKismetMathLibrary::RandomInteger(MyInfected->ComboInfomation.Attacks.Num()) + 1;

	const float AnimTime = MyInfected->PlayAnimMontage(MyInfected->ComboInfomation.Attacks[CurrentComboPlay]);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UBTTask_ZombieAttack::OnTimerFinish,AnimTime,false);
	return EBTNodeResult::InProgress;
}

void UBTTask_ZombieAttack::OnTimerFinish()
{
	++CurrentComboPlay;
	if (CurrentComboPlay == ComboNumber) {
		CurrentComboPlay = 0;
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
	else {
		const float AnimTime = MyInfected->PlayAnimMontage(MyInfected->ComboInfomation.Attacks[CurrentComboPlay]);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_ZombieAttack::OnTimerFinish, AnimTime, false);
	}
}
