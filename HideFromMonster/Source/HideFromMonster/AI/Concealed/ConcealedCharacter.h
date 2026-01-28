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
	
	// Mesh Component that will be used to contain the vertex animation we create
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMeshComponent* ConcealedMesh; 
	
	// Mesh of the vertex animation Idle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMesh* ConcealedMeshIdle;
	
	// Mesh of the vertex animation walk
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConcealedMesh")
	UStaticMesh* ConcealedMeshWalk;

};
