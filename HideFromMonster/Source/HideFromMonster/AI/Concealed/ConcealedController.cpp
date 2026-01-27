// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcealedController.h"

#include "ConcealedCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AConcealedController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ConcealedCharacter = Cast<AConcealedCharacter>(InPawn);

	if (ConcealedCharacter)
	{
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/TopDown/AI/Concealed/BT_Concealed.BT_Concealed"));

		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);

			BlackboardComp = GetBlackboardComponent();
			BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Behavior Tree"));
	}
}
