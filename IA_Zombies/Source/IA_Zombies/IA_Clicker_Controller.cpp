#include "IA_Clicker_Controller.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "GameFramework/Character.h"



AIA_Clicker_Controller::AIA_Clicker_Controller()
{
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;
	if (PerceptionComponent) {
		PerceptionComponent->SetDominantSense(HearingConfig->GetSenseImplementation());
	}
}

void AIA_Clicker_Controller::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* InfectedChar = Cast<ACharacter>(GetPawn());
	UCharacterMovementComponent* MovemenComponent = InfectedChar ? InfectedChar->GetCharacterMovement() : nullptr;
	if (Stimulus.WasSuccessfullySensed()) {
		if (MovemenComponent) {
			MovemenComponent->MaxWalkSpeed = 300.f;
		}
		 if (IsValidStimulus<UAISense_Hearing>(Stimulus)) {
			ManageHearing(Stimulus.StimulusLocation);
		}
	}
	else {
		if (MovemenComponent) {
			MovemenComponent->MaxWalkSpeed = 50.f;
		}
		BlackboardComponent->ClearValue("HearingLocation");
	}
}
