// Fill out your copyright notice in the Description page of Project Settings.


#include "HiveMindActor.h"

#include "HideFromMonster/AI/Monster/MonsterCharacter.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogHiveMindActor);

// Sets default values
AHiveMindActor::AHiveMindActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHiveMindActor::BeginPlay()
{
	Super::BeginPlay();
	if (const UWorld* World = GetWorld())
	{
		AMonsterCharacter* Character = Cast<AMonsterCharacter>(UGameplayStatics::GetActorOfClass(World,
			AMonsterCharacter::StaticClass()));

		if (Character)
			MonsterChara = Character;

		if (MonsterChara)
			UE_LOG(LogHiveMindActor, Warning, TEXT("Monster Chara : %s"), *MonsterChara->GetActorLabel());
	}
}

// Called every frame
void AHiveMindActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (UWorld* World = GetWorld())
	{
		/*UKismetSystemLibrary::SphereOverlapActors(World, MonsterChara->GetActorLocation(), SearchRadius, 
			, ActorToSearch);*/
	}
	
}
