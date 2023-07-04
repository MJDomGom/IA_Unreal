#include "IA_SMOverlap.h"
#include "Components/SphereComponent.h"
#include "IA_BaseInfected_Char.h"

AIA_SMOverlap::AIA_SMOverlap() : Super()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
}

void AIA_SMOverlap::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AIA_SMOverlap::OnComponentBeginOverlap);
}

void AIA_SMOverlap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIA_BaseInfected_Char* Infected = Cast<AIA_BaseInfected_Char>(OtherActor);
	if (!Infected) {
		return;
	}
	Infected->SetCurrentSmartObject(this);
}
