#include "IA_SmartObjectPatrol.h"
#include "Components/SplineComponent.h"

void AIA_SmartObjectPatrol::FillSplinePoints()
{
	for (int32 index = 0; index <= SplineComponent->GetNumberOfSplinePoints(); ++index) {
		SplinePoints.Add(SplineComponent->GetLocationAtSplinePoint(index, ESplineCoordinateSpace::World));
	}
}

AIA_SmartObjectPatrol::AIA_SmartObjectPatrol() : Super()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(RootComponent);

#if WITH_EDITOR
	SplineComponent->bDrawDebug = true;
#endif
}

void AIA_SmartObjectPatrol::BeginPlay()
{
	Super::BeginPlay();
	FillSplinePoints();
}

const TArray<FVector>& AIA_SmartObjectPatrol::GetSplinePoints() const{
	return SplinePoints;
}

