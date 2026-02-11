// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiveMindActor.generated.h"

class USphereComponent;
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
	
	// Search radius for the Sphere
	UPROPERTY(EditAnywhere, Category = "SearchActor")
	float SearchRadius = 500.f;

	// function that will handle the system of Character Query
	UFUNCTION()
	void AddCloseController(AActor* OtherActor);

	UFUNCTION()
	void RemoveCloseController(AActor* OtherActor);
	
	// Use to launch the Query
	void LaunchQuery(AController* ControllerQueryHandler);
	
private:
	// Array that contains all the controller currently overlapped by the Sphere in the monster
	UPROPERTY()
	TArray<AController*> OverlappingController;
	
	// Visual in the editor
	UBillboardComponent* Billboard;
};
