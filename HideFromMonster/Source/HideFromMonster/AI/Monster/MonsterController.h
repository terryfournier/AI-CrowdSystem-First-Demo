// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterController.generated.h"

class AMonsterCharacter;

/**
 * 
 */
UCLASS()
class HIDEFROMMONSTER_API AMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this controller's properties
	AMonsterController();

	virtual void OnPossess(APawn* InPawn) override;

	// Blackboard component of the monster
	UBlackboardComponent* BlackboardComponent;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	// Behavior tree of the monster
	// Note : The tree can also be added via UPROPERTY 
	UBehaviorTree* BehaviorTree;

	// The character this controller possess
	AMonsterCharacter* MonsterCharacter;
	
	// The current Target of the monster
	AActor* TargetActor;
	
	
	// Target management for the monster it will set the new target actor while take into account the distance to them
	void SetNewTargetActor(AActor* NewTargetActor,const FVector& TargetLocation, const bool bStimulusSuccessfullySensed);
	
	void GetCloserActor(AActor* NewTargetActor,const FVector& TargetLocation, const bool bStimulusSuccessfullySensed);
	
	// The behavior for the perception update system
	UFUNCTION()
	void HandleSight(AActor* Actor, FAIStimulus Stimulus);
};
