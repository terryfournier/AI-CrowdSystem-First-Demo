// Fill out your copyright notice in the Description page of Project Settings.


#include "BrainlessCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ABrainlessCharacter::ABrainlessCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating the capsule collider
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleCollider"));
	CapsuleCollider->SetCollisionProfileName(FName("Pawn"));
	RootComponent = CapsuleCollider;

	// Creating IdleMesh with no collision
	BrainlessIdleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BrainlessIdleMesh"));
	BrainlessIdleMesh->SetupAttachment(CapsuleCollider);
	BrainlessIdleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Creating WalkMesh with no collision and Disable visility
	BrainlessWalkMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BrainlessWalkMesh"));
	BrainlessWalkMesh->SetupAttachment(CapsuleCollider);
	BrainlessWalkMesh->SetVisibility(false);
	BrainlessWalkMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABrainlessCharacter::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
}

// Called every frame
void ABrainlessCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor)
		BrainlessMovementActivate(TargetActor->GetActorLocation());
}

void ABrainlessCharacter::BrainlessMovementActivate(FVector NewTargetLocation)
{
	if (!World)
		return;

	// Activate Walking mesh
	ToggleMesh(false);

	// Using DeltaSecond of the world
	float DeltaSeconds = World->GetDeltaSeconds();
	StepSize = Speed * DeltaSeconds;

	// Update location and launching movement
	TargetLocation = NewTargetLocation;
	CurrentLocation = GetActorLocation();
	MoveToLocation(DeltaSeconds);
}

void ABrainlessCharacter::MoveToLocation(const float DeltaSeconds)
{
	// Creating Horizontal Direction 
	FVector HorizontalDirection = GetHorizontalDirection();
	HorizontalDirection = HorizontalDirection.GetSafeNormal();

	//Applying Gravity to the move vector
	FVector MoveVector = (HorizontalDirection * StepSize) + AppliedGravity(DeltaSeconds);

	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

	//Put the actor on the location
	if (StepSize >= DistanceToTarget)
	{
		ToggleMesh(true);
		SetActorLocation(TargetLocation, false);
		return;
	}

	// Set the new location using collision and Hit
	FHitResult HitResult;
	SetActorLocation(CurrentLocation + MoveVector * StepSize, true, &HitResult);

	// If collision we handle the location
	if (HitResult.bBlockingHit)
	{
		HandlingCollision(HitResult);
	}

	// New rotation for the actor
	LookAt();
}

// Gravity Handling using world gravity
FVector ABrainlessCharacter::AppliedGravity(const float DeltaSeconds) const
{
	return FVector(0.f, 0.f, World->GetGravityZ() * 0.5f * DeltaSeconds);;
}

void ABrainlessCharacter::HandlingCollision(const FHitResult& HitResult)
{
	if (HitResult.Time == 0.f)
	{
		// If the actor is stuck we get him out of here using the penetration depth
		FVector DepenetrationVector = HitResult.ImpactNormal * (HitResult.PenetrationDepth + 0.1f);
		SetActorLocation(CurrentLocation + DepenetrationVector, false);
	}
	else
	{
		// Set the actor location to the Hit location
		SetActorLocation(HitResult.Location, false);
	}

	// Create a vector to slide along the wall we hit 
	FVector SlideDirection = FVector::VectorPlaneProject(GetHorizontalDirection(),
	                                                     HitResult.ImpactNormal).GetSafeNormal();

	// How much step until the end of the wall
	FVector RemainingStep = SlideDirection * StepSize;

	// Sliding along the wall
	FHitResult SlideHit;
	SetActorLocation(GetActorLocation() + RemainingStep, true, &SlideHit);

	// if there is a collision we locate the actor to the location
	if (SlideHit.bBlockingHit)
	{
		SetActorLocation(SlideHit.Location, false);
	}
}

// Look at the target function
void ABrainlessCharacter::LookAt()
{
	FRotator NewRotation = FRotationMatrix::MakeFromX(GetHorizontalDirection()).Rotator();
	SetActorRotation(NewRotation);
}

// Get the vector beetween the actor and his target only in 2D
FVector ABrainlessCharacter::GetHorizontalDirection()
{
	FVector HorizontalDirection = (TargetLocation - CurrentLocation);
	HorizontalDirection.Z = 0.f;
	return HorizontalDirection;
}

// Handling the Displayed Mesh on screen 
void ABrainlessCharacter::ToggleMesh(const bool Idle)
{
	BrainlessIdleMesh->SetVisibility(Idle);
	BrainlessWalkMesh->SetVisibility(!Idle);
}
