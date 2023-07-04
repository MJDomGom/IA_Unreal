#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ZombieAttack.generated.h"

class UBehaviorTreeComponent;
class AIA_BaseInfected_Char;

UCLASS()
class IA_ZOMBIES_API UBTTask_ZombieAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ZombieAttack();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY()
		TObjectPtr<UBehaviorTreeComponent> MyOwnerComp = nullptr;
	UPROPERTY()
		TObjectPtr<AIA_BaseInfected_Char> MyInfected = nullptr;
	int32 ComboNumber = 0;
	int32 CurrentComboPlay = 0;
	FTimerHandle TimerHandle;
	void OnTimerFinish();
};
