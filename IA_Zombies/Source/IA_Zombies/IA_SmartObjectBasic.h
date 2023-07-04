// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IA_SmartObjectBasic.generated.h"

class USmartObjectComponent;

UCLASS()
class IA_ZOMBIES_API AIA_SmartObjectBasic : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere,Category ="AI")
		USmartObjectComponent* SmartObjectComponent = nullptr;
	AIA_SmartObjectBasic();

};
