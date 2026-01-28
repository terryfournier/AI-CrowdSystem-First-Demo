// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMove.h"

#include "AIController.h"
#include "MonsterCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_RandomMove::UBTTask_RandomMove()
{
	// Constraint for the key we can pick here only vector can be selected
	LocationContainerKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RandomMove, LocationContainerKey));
}

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory)
{
	// The controller that use this task
	AAIController* MyAIController = Cast<AAIController>(RootComp.GetAIOwner());
	
	// The current navmesh of the world
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (MyAIController && NavSystem)
	{
		const FVector Origin = MyAIController->GetPawn()->GetActorLocation();
		FNavLocation Location;

		// Get a new location in the world that can be reach by the AI 
		if (NavSystem->GetRandomPointInNavigableRadius(Origin, Radius, Location))
		{
			// Set the new target for tha AI to go to 
			MyAIController->GetBlackboardComponent()->SetValueAsVector(
				LocationContainerKey.SelectedKeyName, Location);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
