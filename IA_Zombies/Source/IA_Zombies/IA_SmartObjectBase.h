#pragma once

#include "CoreMinimal.h"
#include "IA_SmartObjectBase.generated.h"

class UBehaviorTree;
class UBillboardComponent;
class UArrowComponent;

UCLASS()
class IA_ZOMBIES_API AIA_SmartObjectBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBillboardComponent* BillboardComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UArrowComponent* ArrowComponent = nullptr;
	AIA_SmartObjectBase();
};

