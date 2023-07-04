#include "IA_BaseInfected_Controller.h"
#include "IA_BaseInfected_Char.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IA_SmartObjectBase.h"
#include "IA_SmartObject_Quiet.h"

AIA_BaseInfected_Controller::AIA_BaseInfected_Controller() : Super()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Config Sight"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Sight"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	SightConfig->SightRadius = 300.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 20.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = false;

	PerceptionComponent->ConfigureSense(*HearingConfig);
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

FGenericTeamId AIA_BaseInfected_Controller::GetGenericTeamId() const
{
	AIA_BaseInfected_Char* Infected = Cast<AIA_BaseInfected_Char>(GetPawn());
	return Infected ? FGenericTeamId(Infected->CurrentTeam) : FGenericTeamId();
}


void AIA_BaseInfected_Controller::BeginPlay()
{
	Super::BeginPlay();
	if (!CurrentAgent) {
		return;
	}
	SmartObjectChanged(CurrentAgent->CurrentSmartObject);
	if (AIA_SmartObject_Quiet* Quiet = Cast<AIA_SmartObject_Quiet>(CurrentAgent->CurrentSmartObject)) {
		BlackboardComponent->SetValueAsVector("InitPosition", Quiet->InitTransform.GetLocation());

	}
}

void AIA_BaseInfected_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIA_BaseInfected_Char* Infected = Cast<AIA_BaseInfected_Char>(InPawn);
	UBehaviorTree* BehaviorTree = Infected ? Infected->BehaviorTree : nullptr;
	if (BehaviorTree) {
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}

	CurrentAgent = Cast<AIA_BaseInfected_Char>(GetPawn());
	CurrentAgent->OnSmartObjectChanged.BindUObject(this, &AIA_BaseInfected_Controller::SmartObjectChanged);
	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AIA_BaseInfected_Controller::OnTargetPerceptionUpdated);
}

void AIA_BaseInfected_Controller::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {
	ACharacter* InfectedChar = Cast<ACharacter>(GetPawn());
	UCharacterMovementComponent* MovemenComponent = InfectedChar ? InfectedChar->GetCharacterMovement() : nullptr;
	if (Stimulus.WasSuccessfullySensed()) {

		if (MovemenComponent) {
			MovemenComponent->MaxWalkSpeed = 300.f;
		}

		if (IsValidStimulus<UAISense_Sight>(Stimulus) && bCanUseSight) {
			ManageSight(Actor);
		}
		else if (IsValidStimulus<UAISense_Hearing>(Stimulus)) {
			ManageHearing(Stimulus.StimulusLocation);
		}
	}
	else {

		if (MovemenComponent) {
			MovemenComponent->MaxWalkSpeed = 50.f;
		}
		if (bCanUseSight) {
			ManageSight(nullptr);
		}
		BlackboardComponent->ClearValue("HearingLocation");
	}
}

void AIA_BaseInfected_Controller::ManageSight(AActor* Actor)
{
	BlackboardComponent->SetValue<UBlackboardKeyType_Object>("TargetActor", Actor);
	BlackboardComponent->ClearValue("HearingLocation");
}

void AIA_BaseInfected_Controller::ManageHearing(const FVector& HearingLocation)
{
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>("HearingLocation", HearingLocation);
}

void AIA_BaseInfected_Controller::SmartObjectChanged(AIA_SmartObjectBase* NewSmartObject)
{
	if (NewSmartObject) {
		FGameplayTag SubTag;
		BehaviorTreeComponent->SetDynamicSubtree(SubTag, NewSmartObject->BehaviorTree);
	}
}


