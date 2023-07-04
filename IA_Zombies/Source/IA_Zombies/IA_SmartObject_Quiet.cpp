#include "IA_SmartObject_Quiet.h"
#include "Components/SceneComponent.h"

AIA_SmartObject_Quiet::AIA_SmartObject_Quiet() : Super()
{
	PointToLook = CreateDefaultSubobject<USceneComponent>(TEXT("Point To Look"));
	PointToLook->SetupAttachment(RootComponent);
}

void AIA_SmartObject_Quiet::BeginPlay()
{
	Super::BeginPlay();
	if (InitActor.Get()) {
		InitTransform = InitActor.Get()->GetActorTransform();
	}
	else {
		InitTransform = GetActorTransform();
	}
}
