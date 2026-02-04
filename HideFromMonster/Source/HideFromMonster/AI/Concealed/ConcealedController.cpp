// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcealedController.h"

#include "ConcealedCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void AConcealedController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Founding the character we possessed
	ConcealedCharacter = Cast<AConcealedCharacter>(InPawn);

	if (ConcealedCharacter)
	{
		/*// Load the behavior tree for the monster
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/TopDown/AI/Concealed/BT_Concealed.BT_Concealed"));

		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);

			// Creation and Initialisation of the blackboard of this controller// Creation and Initialisation of the blackboard of this controller
			BlackboardComp = GetBlackboardComponent();
			BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Behavior Tree"));
	}
}

void AConcealedController::LaunchQuery_Implementation()
{
	HideQuery = LoadObject<UEnvQuery>(nullptr, TEXT("/Game/TopDown/AI/EQS/EQS_Find.EQS_Find"));
	
	if (HideQuery)
	{
		// Creation of the query request
		HideQueryRequest = new FEnvQueryRequest(HideQuery, this);
	}
	HideQueryRequest->Execute(EEnvQueryRunMode::SingleResult, this, &AConcealedController::HideQueryAction);
}

void AConcealedController::HideQueryAction(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccessful())
	{
		MoveToLocation(Result->GetItemAsLocation(0));
	}
}
