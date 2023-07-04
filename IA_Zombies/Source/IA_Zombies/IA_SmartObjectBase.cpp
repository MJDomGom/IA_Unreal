#include "IA_SmartObjectBase.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"

AIA_SmartObjectBase::AIA_SmartObjectBase() : Super()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard Component"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));

	ArrowComponent->SetupAttachment(RootComponent);
	BillboardComponent->SetupAttachment(RootComponent);
}
