#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionSystem.h"
#include "IA_BaseInfected_Controller.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class AIA_BaseInfected_Char;
class AIA_SmartObjectBase;

UENUM()
enum class ETeams : uint8
{
	Zombies,
	Humanos
};


UCLASS()
class IA_ZOMBIES_API AIA_BaseInfected_Controller : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Sight* SightConfig = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UAISenseConfig_Hearing* HearingConfig = nullptr;
	UPROPERTY(EditDefaultsOnly)
		bool bCanUseSight = true;
	AIA_BaseInfected_Controller();
	virtual FGenericTeamId GetGenericTeamId() const override;


protected:
	UPROPERTY();
		AIA_BaseInfected_Char* CurrentAgent = nullptr;

	virtual void BeginPlay() override;
	void ManageHearing(const FVector& HearingLocation);
	virtual void OnPossess(APawn* InPawn) override;

	template <class T>
	bool IsValidStimulus(FAIStimulus Stimulus)
	{
		return UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == T::StaticClass();
	}
private:
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


	void ManageSight(AActor* Actor);
	void SmartObjectChanged(AIA_SmartObjectBase* NewSmartObject);
};
