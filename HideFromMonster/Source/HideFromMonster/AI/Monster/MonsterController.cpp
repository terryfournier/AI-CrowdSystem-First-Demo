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

	UAISenseConfig_Sight* MySightSenses = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	MySightSenses->SightRadius = 1000.f;
	MySightSenses->LoseSightRadius = 1050.f;
	MySightSenses->PeripheralVisionAngleDegrees = 90.f;
	MySightSenses->DetectionByAffiliation.bDetectEnemies = true;
	MySightSenses->DetectionByAffiliation.bDetectNeutrals = true;
	MySightSenses->DetectionByAffiliation.bDetectFriendlies = true;
	MySightSenses->SetMaxAge(0.1f);

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	PerceptionComponent->ConfigureSense(*MySightSenses);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	MonsterCharacter = Cast<AMonsterCharacter>(InPawn);
	
	if (MonsterCharacter)
	{
		BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/TopDown/AI/Monster/BT_Monster.BT_Monster"));
		
		if (BehaviorTree)
		{
			RunBehaviorTree(BehaviorTree);

			BlackboardComponent = GetBlackboardComponent();
			BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
		
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

void AMonsterController::SetNewTargetActor(AActor* NewTargetActor, const FVector& TargetLocation,
	const bool bStimulusSuccessfullySensed)
{
	TargetActor = NewTargetActor;
	if (bStimulusSuccessfullySensed)
	{
		BlackboardComponent->SetValueAsObject("TargetActor", TargetActor);
	}
	else
	{
		BlackboardComponent->ClearValue("TargetActor");
		BlackboardComponent->SetValueAsVector("LastKnownLocation", TargetLocation);
	}
}

void AMonsterController::GetCloserActor(AActor* NewTargetActor, const FVector& TargetLocation,
	const bool bStimulusSuccessfullySensed)
{
	if (MonsterCharacter && MonsterCharacter->GetDistanceTo(NewTargetActor) < MonsterCharacter->GetDistanceTo(TargetActor))
	{
		SetNewTargetActor(NewTargetActor, TargetLocation, bStimulusSuccessfullySensed);
	}
}

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
