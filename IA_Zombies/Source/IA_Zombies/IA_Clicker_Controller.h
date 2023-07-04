#pragma once

#include "CoreMinimal.h"
#include "IA_BaseInfected_Controller.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "IA_Clicker_Controller.generated.h"

UCLASS()
class IA_ZOMBIES_API AIA_Clicker_Controller : public AIA_BaseInfected_Controller
{
	GENERATED_BODY()
public:
	AIA_Clicker_Controller();

private:
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
};
