// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_KillTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_KillTarget::UBTTask_KillTarget()
{
	// Add a filter so the user can only choose actor
	ActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_KillTarget, ActorKey), 
		AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_KillTarget::ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory)
{
	// Destroy the actor in the given key
	if (const UBlackboardComponent* BlackboardComponent = RootComp.GetAIOwner()->GetBlackboardComponent())
	{
		if (AActor* Actor =  Cast<AActor>(BlackboardComponent->GetValueAsObject(ActorKey.SelectedKeyName)))
		{
			Actor->Destroy();
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
