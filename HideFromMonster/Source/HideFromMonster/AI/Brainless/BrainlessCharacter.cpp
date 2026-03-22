// Fill out your copyright notice in the Description page of Project Settings.


#include "BrainlessCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ABrainlessCharacter::ABrainlessCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleCollider"));
	CapsuleCollider->SetCollisionProfileName(FName("Pawn"));
	RootComponent = CapsuleCollider;

	BrainlessIdleMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BrainlessIdleMesh"));
	BrainlessIdleMesh->SetupAttachment(CapsuleCollider);
	BrainlessIdleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

void ABrainlessCharacter::BrainlessMovementActivate(FVector TargetLocation)
{
	if (!World)
		return;
	ToggleMesh(false);

	float DeltaSeconds = World->GetDeltaSeconds();
	StepSize = Speed * DeltaSeconds;

	CurrentLocation = GetActorLocation();
	MoveToLocation(TargetLocation, DeltaSeconds);
}

void ABrainlessCharacter::MoveToLocation(FVector TargetLocation, const float DeltaSeconds)
{
	FVector HorizontalDirection = GetHorizontalDirection(TargetLocation);
	HorizontalDirection = HorizontalDirection.GetSafeNormal();

	FVector MoveVector = (HorizontalDirection * StepSize) + AppliedGravity(DeltaSeconds);

	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

	if (StepSize >= DistanceToTarget)
	{
		ToggleMesh(true);
		SetActorLocation(TargetLocation, false);
		return;
	}

	FHitResult HitResult;
	SetActorLocation(CurrentLocation + MoveVector * StepSize, true, &HitResult);

	if (HitResult.bBlockingHit)
	{
		// --- Depenetration ---
		if (HitResult.Time == 0.f)
		{
			FVector DepenetrationVector = HitResult.ImpactNormal * (HitResult.PenetrationDepth + 0.1f);
			// small bias to fully clear the wall
			SetActorLocation(CurrentLocation + DepenetrationVector, false);
		}
		else
		{
			// Normal hit — move to safe location just before impact
			SetActorLocation(HitResult.Location, false);
		}

		// --- Slide along the wall ---
		FVector SlideDirection = FVector::VectorPlaneProject(HorizontalDirection, HitResult.ImpactNormal).
			GetSafeNormal();

		// Apply remaining slide movement
		FVector RemainingStep = SlideDirection * StepSize;

		// Sweep again for the slide to avoid clipping into corners
		FHitResult SlideHit;
		SetActorLocation(GetActorLocation() + RemainingStep, true, &SlideHit);

		if (SlideHit.bBlockingHit)
		{
			SetActorLocation(SlideHit.Location, false);
		}
	}

	LookAt(TargetLocation);
}

FVector ABrainlessCharacter::AppliedGravity(const float DeltaSeconds) const
{
	return FVector(0.f, 0.f, World->GetGravityZ() * 0.5f * DeltaSeconds);;
}

void ABrainlessCharacter::LookAt(const FVector& TargetLocation)
{
	FRotator NewRotation = FRotationMatrix::MakeFromX(GetHorizontalDirection(TargetLocation)).Rotator();
	SetActorRotation(NewRotation);
}

FVector ABrainlessCharacter::GetHorizontalDirection(const FVector& TargetLocation)
{
	FVector HorizontalDirection = (TargetLocation - CurrentLocation);
	HorizontalDirection.Z = 0.f;
	return HorizontalDirection;
}

void ABrainlessCharacter::ToggleMesh(const bool Idle)
{
	BrainlessIdleMesh->SetVisibility(Idle);
	BrainlessWalkMesh->SetVisibility(!Idle);
}
