// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiveMindActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHiveMindActor, Log, All);

class AMonsterCharacter;

UCLASS()
class HIDEFROMMONSTER_API AHiveMindActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHiveMindActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "SearchActor")
	UClass* ActorToSearch;
	
	UPROPERTY(EditAnywhere, Category = "SearchActor")
	float SearchRadius = 500.f;
	
	AMonsterCharacter* MonsterChara;
	
	
	
};
