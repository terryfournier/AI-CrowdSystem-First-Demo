// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ConcealedCharacter.generated.h"

UCLASS()
class HIDEFROMMONSTER_API AConcealedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AConcealedCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMeshComponent* ConcealedMesh; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMesh* ConcealedMeshIdle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMesh* ConcealedMeshWalk;

};
