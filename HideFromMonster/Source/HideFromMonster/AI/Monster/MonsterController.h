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

	UBlackboardComponent* BlackboardComponent;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	UBehaviorTree* BehaviorTree;

	AMonsterCharacter* MonsterCharacter;
	
	AActor* TargetActor;
	
	void SetNewTargetActor(AActor* NewTargetActor,const FVector& TargetLocation, const bool bStimulusSuccessfullySensed);
	
	void GetCloserActor(AActor* NewTargetActor,const FVector& TargetLocation, const bool bStimulusSuccessfullySensed);
	
	UFUNCTION()
	void HandleSight(AActor* Actor, FAIStimulus Stimulus);

	/*UPROPERTY(EditAnywhere)
	FBlackboardKeySelector KeySelector;*/
};
