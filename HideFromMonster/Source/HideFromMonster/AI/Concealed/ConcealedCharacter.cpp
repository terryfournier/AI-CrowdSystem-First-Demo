// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcealedCharacter.h"

#include "ConcealedController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AConcealedCharacter::AConcealedCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Note : Some of this settings might not be change in a realistic production due to the lack of knowledge about 
	// the monster mesh and characteristic
	
	// Create the Mesh component and attach it to the root which his the capsule in a character
	ConcealedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConcealedMesh"));
	ConcealedMesh->SetupAttachment(RootComponent);
	
	ConcealedMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	ConcealedMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	// Apply the correct position for the mesh to be used
	// Moreover this mesh will be hide in game to fully used the vertex animation
	if (USkeletalMeshComponent* SkeletalMesh = GetMesh())
	{
		SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		SkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		SkeletalMesh->SetHiddenInGame(true);
	}
	
	// Apply specific data to the movement of the monster
	if (UCharacterMovementComponent* CharaMovement = GetCharacterMovement())
	{
		CharaMovement->MaxWalkSpeed = 150.f;
		CharaMovement->MaxWalkSpeedCrouched = 150.f;
		CharaMovement->bUseControllerDesiredRotation = true;
	}
	
	bUseControllerRotationYaw = false;
	
	// Set up the possess behavior to be launched at the right time
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// Adding the concealed controller 
	AIControllerClass = AConcealedController::StaticClass();
	
	// Add a tag to identify the character when we want to kill it
	Tags.Add("Concealed");
}

// Called when the game starts or when spawned
void AConcealedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set the Idle mesh by default
	if (ConcealedMeshIdle)
		ConcealedMesh->SetStaticMesh(ConcealedMeshIdle);
}

// Called every frame
void AConcealedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update the mesh using the velocity of the character
	if (ConcealedMeshIdle && ConcealedMeshWalk)
	{
		if (GetVelocity().IsNearlyZero())
			ConcealedMesh->SetStaticMesh(ConcealedMeshIdle);
		else
			ConcealedMesh->SetStaticMesh(ConcealedMeshWalk);
	}
}

// Called to bind functionality to input
void AConcealedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

