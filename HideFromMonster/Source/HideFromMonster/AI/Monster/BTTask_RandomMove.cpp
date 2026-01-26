// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMove.h"

#include "AIController.h"
#include "MonsterCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_RandomMove::UBTTask_RandomMove()
{
	LocationContainerKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RandomMove, LocationContainerKey));
}

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory)
{
	AAIController* MyAIController = Cast<AAIController>(RootComp.GetAIOwner());
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (MyAIController && NavSystem)
	{
		const FVector Origin = MyAIController->GetPawn()->GetActorLocation();
		FNavLocation Location;

		if (NavSystem->GetRandomPointInNavigableRadius(Origin, Radius, Location))
		{
			MyAIController->GetBlackboardComponent()->SetValueAsVector(
				LocationContainerKey.SelectedKeyName, Location);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
