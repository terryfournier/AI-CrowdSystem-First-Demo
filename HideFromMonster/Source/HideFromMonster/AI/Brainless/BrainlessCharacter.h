// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrainlessCharacter.generated.h"

class UCapsuleComponent;

UCLASS()
class HIDEFROMMONSTER_API ABrainlessCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrainlessCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brainless")
	UCapsuleComponent* CapsuleCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brainless")
	UStaticMeshComponent* BrainlessIdleMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brainless")
	UStaticMeshComponent* BrainlessWalkMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brainless")
	float Speed = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brainless")
	AActor* TargetActor;
	
	void BrainlessMovementActivate(FVector TargetLocation);
	
private:
	UWorld* World;
	
	float StepSize = 1.0f;
	
	FVector CurrentLocation;
	
	void MoveToLocation(FVector TargetLocation, const float DeltaSeconds);
	
	FVector AppliedGravity(const float DeltaSeconds) const;
	
	void LookAt(const FVector& TargetLocation);
	
	FVector GetHorizontalDirection(const FVector& TargetLocation);
	
	void ToggleMesh(const bool Idle);
};
