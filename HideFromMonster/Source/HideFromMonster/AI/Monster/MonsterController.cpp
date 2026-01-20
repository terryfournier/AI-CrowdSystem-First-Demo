// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
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
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterController::HandleSight);
	
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (!BehaviorTree)
	{
		BehaviorTree = NewObject<UBehaviorTree>(this, TEXT("BehaviorTree"));
		BehaviorTree->BlackboardAsset = NewObject<UBlackboardData>(this, TEXT("BlackboardData"));
		
		FBlackboardEntry SelfActorEntry;
		SelfActorEntry.EntryName = "SelfActor";
		SelfActorEntry.KeyType = NewObject<UBlackboardKeyType_Object>(BehaviorTree->BlackboardAsset);
		BehaviorTree->BlackboardAsset->Keys.Add(SelfActorEntry);
		
		FBlackboardEntry TargetActorEntry;
		SelfActorEntry.EntryName = "TargetActor";
		SelfActorEntry.KeyType = NewObject<UBlackboardKeyType_Object>(BehaviorTree->BlackboardAsset);
		BehaviorTree->BlackboardAsset->Keys.Add(TargetActorEntry);
		
		FBlackboardEntry LastKnownLocationEntry;
		SelfActorEntry.EntryName = "LastKnownLocation";
		SelfActorEntry.KeyType = NewObject<UBlackboardKeyType_Vector>(BehaviorTree->BlackboardAsset);
		BehaviorTree->BlackboardAsset->Keys.Add(LastKnownLocationEntry);
		
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		
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

void AMonsterController::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> senseConfig = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);
	
	if (senseConfig == UAISense_Sight::StaticClass() && Actor->ActorHasTag("Concealed"))
	{
		
	}
}
