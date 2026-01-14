// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRenamed.h"

// Sets default values
AActorRenamed::AActorRenamed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorRenamed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorRenamed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

