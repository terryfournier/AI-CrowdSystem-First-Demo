// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BehaviorTree;
	
	UFUNCTION()
	void HandleSight(AActor* Actor, FAIStimulus Stimulus);
	
	/*UPROPERTY(EditAnywhere)
	FBlackboardKeySelector KeySelector;*/
};
