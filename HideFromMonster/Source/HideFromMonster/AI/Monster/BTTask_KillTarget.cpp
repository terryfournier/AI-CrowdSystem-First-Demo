// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_KillTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_KillTarget::UBTTask_KillTarget()
{
	ActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_KillTarget, ActorKey), 
		AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_KillTarget::ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComponent = RootComp.GetAIOwner()->GetBlackboardComponent())
	{
		if (AActor* Actor =  Cast<AActor>(BlackboardComponent->GetValueAsObject(ActorKey.SelectedKeyName)))
		{
			Actor->Destroy();
		}
	}
	
	
	return Super::ExecuteTask(RootComp, NodeMemory);
}
