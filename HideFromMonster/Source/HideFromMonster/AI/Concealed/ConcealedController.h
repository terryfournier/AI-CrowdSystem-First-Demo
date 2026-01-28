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
	// Blackboard component of the concealed
	UBlackboardComponent* BlackboardComp;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	// Behavior tree of the concealed
	// Note : The tree can also be added via UPROPERTY 
	UBehaviorTree* BehaviorTree;
	
	// The character this controller possess
	AConcealedCharacter* ConcealedCharacter;
};
