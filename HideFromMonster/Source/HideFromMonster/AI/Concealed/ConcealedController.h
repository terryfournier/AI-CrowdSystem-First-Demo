// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HideFromMonster/Interface/LaunchQueryInterface.h"
#include "ConcealedController.generated.h"

class AHiveMindActor;
struct FEnvQueryResult;
struct FEnvQueryRequest;
class UEnvQuery;
class AConcealedCharacter;
/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API AConcealedController : public AAIController, public ILaunchQueryInterface
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	
	// Run the query when we need using the interface
	virtual void LaunchQuery_Implementation() override;
	
private:
	// Blackboard component of the concealed
	UBlackboardComponent* BlackboardComp;
	
	// Reference to the Hive Mind Actor
	AHiveMindActor* HiveMindActor;
	
	// The character this controller possess
	AConcealedCharacter* ConcealedCharacter;
	
	// Behavior tree of the concealed
	// Note : The tree can also be added via UPROPERTY 
	UBehaviorTree* BehaviorTree;
	
	// Contains the Query we want to launch
	UEnvQuery* HideQuery;
	
	// Request that will be used to launch the querry
	FEnvQueryRequest* HideQueryRequest;
	
	// Function to launch at the end of the query that contains the result
	void HideQueryAction(TSharedPtr<FEnvQueryResult> Result);
};
