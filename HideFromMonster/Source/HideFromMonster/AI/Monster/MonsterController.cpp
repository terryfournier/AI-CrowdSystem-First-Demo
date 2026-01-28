// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "MonsterCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Set default value
AMonsterController::AMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creation of the Sight senses of the monster 
	UAISenseConfig_Sight* MySightSenses = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	MySightSenses->SightRadius = 1000.f;
	MySightSenses->LoseSightRadius = 1050.f;
	MySightSenses->PeripheralVisionAngleDegrees = 90.f;
	MySightSenses->DetectionByAffiliation.bDetectEnemies = true;
	MySightSenses->DetectionByAffiliation.bDetectNeutrals = true;
	MySightSenses->DetectionByAffiliation.bDetectFriendlies = true;
	MySightSenses->SetMaxAge(0.1f);

	// Creation of the perception system of the monster
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// Adding the nes senses to the Perception 
	// Note : No really need for a dominant Senses since there will be only one
	PerceptionComponent->ConfigureSense(*MySightSenses);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Founding the character we possessed
	MonsterCharacter = Cast<AMonsterCharacter>(InPawn);
	
	if (MonsterCharacter)
	{
		// Load the behavior tree for the monster
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/TopDown/AI/Monster/BT_Monster.BT_Monster"));
		
		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);

			// Creation and Initialisation of the blackboard of this controller
			BlackboardComponent = GetBlackboardComponent();
			BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
		
		// Bind the HandleSight function the correct event
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterController::HandleSight);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Behavior Tree"));
	}
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

// Will add the new Target actor to the blackboard
void AMonsterController::SetNewTargetActor(AActor* NewTargetActor, const FVector& TargetLocation,
	const bool bStimulusSuccessfullySensed)
{
	TargetActor = NewTargetActor;
	// Adding the target
	if (bStimulusSuccessfullySensed)
	{
		BlackboardComponent->SetValueAsObject("TargetActor", TargetActor);
	}
	// if the target is lost the value will be cleared and the monster will go to his last location
	else
	{
		BlackboardComponent->ClearValue("TargetActor");
		BlackboardComponent->SetValueAsVector("LastKnownLocation", TargetLocation);
	}
}

// Will calculate which target between the new one and the one in his blackboard is closer
void AMonsterController::GetCloserActor(AActor* NewTargetActor, const FVector& TargetLocation,
	const bool bStimulusSuccessfullySensed)
{
	if (MonsterCharacter && MonsterCharacter->GetDistanceTo(NewTargetActor) < MonsterCharacter->GetDistanceTo(TargetActor))
	{
		SetNewTargetActor(NewTargetActor, TargetLocation, bStimulusSuccessfullySensed);
	}
}

// Handle Sight will choose if the target can be updated using the stimulus 
void AMonsterController::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> senseConfig = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);

	if (senseConfig == UAISense_Sight::StaticClass() && Actor->ActorHasTag("Concealed"))
	{
		TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		
		if (TargetActor)
		{
			GetCloserActor(Actor, Stimulus.StimulusLocation, Stimulus.WasSuccessfullySensed());
		}
		else
		{
			SetNewTargetActor(Actor, Stimulus.StimulusLocation, Stimulus.WasSuccessfullySensed());
		}
	}
}
