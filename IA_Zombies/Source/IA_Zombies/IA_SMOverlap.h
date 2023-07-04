#pragma once

#include "CoreMinimal.h"
#include "IA_SmartObjectBase.h"
#include "IA_SMOverlap.generated.h"

class USphereComponent;

UCLASS()
class IA_ZOMBIES_API AIA_SMOverlap : public AIA_SmartObjectBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponent = nullptr;

	AIA_SMOverlap();
protected:
	void BeginPlay() override;
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
