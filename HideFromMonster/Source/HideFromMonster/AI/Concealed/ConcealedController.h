// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ConcealedController.generated.h"

class AConcealedCharacter;
/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API AConcealedController : public AAIController
{
	GENERATED_BODY()
	
public:
	UBlackboardComponent* BlackboardComp;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	UBehaviorTree* BehaviorTree;
	
	AConcealedCharacter* ConcealedCharacter;
};
