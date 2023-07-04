#pragma once

#include "CoreMinimal.h"
#include "IA_SmartObjectBase.h"
#include "IA_SmartObject_Quiet.generated.h"

class USceneComponent;

UCLASS()
class IA_ZOMBIES_API AIA_SmartObject_Quiet : public AIA_SmartObjectBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TWeakObjectPtr<AActor> InitActor = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* PointToLook = nullptr;


	AIA_SmartObject_Quiet();
	FTransform InitTransform;
	virtual void BeginPlay() override;
};
