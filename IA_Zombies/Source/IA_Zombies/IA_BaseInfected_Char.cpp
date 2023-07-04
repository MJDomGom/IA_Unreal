#include "IA_BaseInfected_Char.h"
#include "IA_BaseInfected_Controller.h"
#include <Components/DrawSphereComponent.h>
#include "Components/SceneComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "IA_ZombiesCharacter.h"




void AIA_BaseInfected_Char::ResetSmartObject()
{
	SetCurrentSmartObject(MainSmartObject);
}

void AIA_BaseInfected_Char::SetCurrentSmartObject(AIA_SmartObjectBase* NewSmartObject)
{
	CurrentSmartObject = NewSmartObject;
	OnSmartObjectChanged.ExecuteIfBound(CurrentSmartObject);
}

AIA_BaseInfected_Char::AIA_BaseInfected_Char() : Super()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	CurrentTeam = static_cast<uint8>(ETeams::Zombies);
}


void AIA_BaseInfected_Char::BeginPlay()
{
	Super::BeginPlay();
	if (CurrentSmartObject) {
		MainSmartObject = CurrentSmartObject;
	}
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AIA_BaseInfected_Char::OnAttackAreaOverlapped);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AIA_BaseInfected_Char::OnAttackEndOverlapped);
}

void AIA_BaseInfected_Char::OnAttackAreaOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetCanAttack(OtherActor, true);
}

void AIA_BaseInfected_Char::OnAttackEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetCanAttack(OtherActor, false);

}

void AIA_BaseInfected_Char::SetCanAttack(AActor* ActorToAttack, bool bCanAttack)
{
	if (!ActorToAttack->IsA<AIA_ZombiesCharacter>()) {
		return;
	}
	AIA_BaseInfected_Controller* MyController = Cast<AIA_BaseInfected_Controller>(GetController());
	if (!MyController) {
		return;
	}
	MyController->BlackboardComponent->SetValueAsBool("CanAttack", bCanAttack);
}


