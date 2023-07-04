#include "IA_SmartObjectBasic.h"
#include "SmartObjectComponent.h"

AIA_SmartObjectBasic::AIA_SmartObjectBasic()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SmartObjectComponent = CreateDefaultSubobject<USmartObjectComponent>(TEXT("SmartObject Component"));
	SmartObjectComponent->SetupAttachment(RootComponent);
}


