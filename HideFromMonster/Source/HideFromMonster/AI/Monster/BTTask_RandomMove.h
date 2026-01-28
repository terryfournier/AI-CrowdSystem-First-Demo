// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API UBTTask_RandomMove : public UBTTaskNode
{
	GENERATED_BODY()
public:	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory);
	
	UBTTask_RandomMove();
	
	// This key will contain the new target of the AI
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LocationContainerKey;
	
	// Radius of the circle in which the target can be selected for the AI to go to
	UPROPERTY(EditAnywhere, Category = "Search")
	float Radius = 5.0f;
};
