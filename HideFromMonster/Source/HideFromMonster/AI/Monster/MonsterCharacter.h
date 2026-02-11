// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

class AHiveMindActor;
class USphereComponent;

UCLASS()
class HIDEFROMMONSTER_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

protected:
	// Overlap Action that will be bind to the sphere collision event 
	// Will be used to launch the action of the HiveMind 
	
	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Sphere used to detect the character that are to close of the monster
	UPROPERTY(EditDefaultsOnly, Category = "HiveMindResearch")
	USphereComponent *SphereCompo;

private:
	// Reference to the Hive Mind 
	AHiveMindActor* HiveMindActor;
};
