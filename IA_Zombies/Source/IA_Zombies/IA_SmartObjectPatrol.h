#pragma once

#include "CoreMinimal.h"
#include "IA_SmartObjectBase.h"
#include "IA_SmartObjectPatrol.generated.h"

class USplineComponent;

UCLASS()
class IA_ZOMBIES_API AIA_SmartObjectPatrol : public AIA_SmartObjectBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Patrol")
		USplineComponent* SplineComponent = nullptr;
	void FillSplinePoints();
	AIA_SmartObjectPatrol();
	const TArray<FVector>& GetSplinePoints() const;

protected:
	void BeginPlay() override;
private:
	UPROPERTY()
		TArray<FVector> SplinePoints;
};

