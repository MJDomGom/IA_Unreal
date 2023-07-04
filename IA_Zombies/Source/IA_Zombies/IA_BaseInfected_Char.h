#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "IA_SmartObjectBase.h"
#include <Components/DrawSphereComponent.h>
#include "IA_BaseInfected_Char.generated.h"



class UBehaviorTree;
class AIA_SmartObjectBase;
class USphereComponent;
class UPrimitiveComponent;


USTRUCT(BlueprintType)
struct FIA_ComboInformation {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
		TArray<UAnimMontage*> Attacks;
};

DECLARE_DELEGATE_OneParam(FOnSmartObjectChanged, AIA_SmartObjectBase*)

UCLASS()
class IA_ZOMBIES_API AIA_BaseInfected_Char : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY(EditAnywhere, Category = AI)
		AIA_SmartObjectBase* CurrentSmartObject = nullptr;
	UPROPERTY()
		AIA_SmartObjectBase* MainSmartObject = nullptr;
	UPROPERTY(EditDefaultsOnly)
		FIA_ComboInformation ComboInfomation;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereComponent = nullptr;

	uint8 CurrentTeam;
	FOnSmartObjectChanged OnSmartObjectChanged;
	void ResetSmartObject();
	void SetCurrentSmartObject(AIA_SmartObjectBase* NewSmartObject);
	AIA_BaseInfected_Char();


protected:
	void BeginPlay() override;
private:

	UFUNCTION()
		void OnAttackAreaOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void SetCanAttack(AActor* ActorToAttack, bool bCanAttack);
};
