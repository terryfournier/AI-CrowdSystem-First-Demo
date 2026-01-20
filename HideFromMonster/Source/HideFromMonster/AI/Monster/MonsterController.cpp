// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
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
}

void AMonsterController::HandleSight(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> senseConfig = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);
	
	if (senseConfig == UAISense_Sight::StaticClass() && Actor->ActorHasTag("Concealed"))
	{
		
	}
}
