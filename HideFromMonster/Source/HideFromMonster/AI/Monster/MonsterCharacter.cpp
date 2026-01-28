// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"

#include "MonsterController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Note : Some of this settings might not be change in a realistic production due to the lack of knowledge about 
	// the monster mesh and characteristic

	// Apply specific data to the movement of the monster
	if (UCharacterMovementComponent* charaMovement = GetCharacterMovement())
	{
		charaMovement->MaxWalkSpeed = 200.0f;
		
		// Make sure the controller as full control of the character rotation
		charaMovement->bUseControllerDesiredRotation = true;
	}
	
	bUseControllerRotationYaw = false;

	// Apply the correct position for the mesh to be used
	if (USkeletalMeshComponent* SkeletalMesh = GetMesh())
	{
		SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		SkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	// Adding the monster controller 
	AIControllerClass = AMonsterController::StaticClass();
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
