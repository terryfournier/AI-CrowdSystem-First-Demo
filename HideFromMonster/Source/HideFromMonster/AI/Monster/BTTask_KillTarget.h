// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_KillTarget.generated.h"

/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API UBTTask_KillTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTTask_KillTarget();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ActorKey;
};
