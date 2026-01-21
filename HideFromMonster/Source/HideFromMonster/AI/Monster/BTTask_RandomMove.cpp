// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMove.h"

#include "AIController.h"
#include "MonsterCharacter.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& RootComp, uint8* NodeMemory)
{
	if (AMonsterCharacter* MonsterCharacter = Cast<AMonsterCharacter>(RootComp.GetAIOwner()->GetPawn()))
	{
		/*if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FVector Origin = MonsterCharacter->GetActorLocation();
			FNavLocation Location;
			NavSystem->GetRandomReachablePointInRadius(Origin, Radius,Location);
			
		}*/
	}
	return Super::ExecuteTask(RootComp, NodeMemory);
}
