// Fill out your copyright notice in the Description page of Project Settings.


#include "ConcealedCharacter.h"

#include "ConcealedController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AConcealedCharacter::AConcealedCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ConcealedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConcealedMesh"));
	ConcealedMesh->SetupAttachment(RootComponent);
	
	ConcealedMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	ConcealedMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	if (USkeletalMeshComponent* SkeletalMesh = GetMesh())
	{
		SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		SkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		SkeletalMesh->SetHiddenInGame(true);
	}
	
	if (UCharacterMovementComponent* CharaMovement = GetCharacterMovement())
	{
		CharaMovement->MaxWalkSpeed = 150.f;
		CharaMovement->MaxWalkSpeedCrouched = 150.f;
		CharaMovement->bUseControllerDesiredRotation = true;
	}
	
	bUseControllerRotationYaw = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	AIControllerClass = AConcealedController::StaticClass();
	
	Tags.Add("Concealed");
}

// Called when the game starts or when spawned
void AConcealedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ConcealedMeshIdle)
		ConcealedMesh->SetStaticMesh(ConcealedMeshIdle);
}

// Called every frame
void AConcealedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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

