// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this controller's properties
	AMonsterController();
private:
	UFUNCTION()
    	void HandleSight(AActor* Actor, FAIStimulus Stimulus);
};
