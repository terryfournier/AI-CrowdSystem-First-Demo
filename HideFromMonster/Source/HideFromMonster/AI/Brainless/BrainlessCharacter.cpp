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

	if (TargetActor)
		BrainlessMovementActivate(TargetActor->GetActorLocation());
}

// Called every frame
void ABrainlessCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrainlessCharacter::BrainlessMovementActivate(FVector TargetLocation)
{
	ToggleMesh(false);
	MoveToLocation(TargetLocation);
}

void ABrainlessCharacter::MoveToLocation(FVector TargetLocation)
{
	if (!World)
		return;

	World->GetTimerManager().SetTimer(MovementTimerHandle, [this, TargetLocation]()
	{
		float DeltaSeconds = GetWorld()->GetDeltaSeconds();
		StepSize = Speed * DeltaSeconds;
		const FVector CurrentLocation = GetActorLocation();
		
		// --- 1. Pure horizontal direction toward target, never accumulates ---
		FVector HorizontalDirection = (TargetLocation - CurrentLocation);
		HorizontalDirection.Z = 0.f;
		HorizontalDirection = HorizontalDirection.GetSafeNormal();

		// --- 2. Gravity is its own separate vector, applied independently ---
		FVector GravityThisFrame = FVector(0.f, 0.f, World->GetGravityZ() * 0.5f * DeltaSeconds);

		// --- 3. Final movement = horizontal + gravity, computed fresh every frame ---
		FVector MoveVector = (HorizontalDirection * StepSize) + GravityThisFrame;
		
		float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

		if (StepSize >= DistanceToTarget)
		{
			ToggleMesh(true);
			SetActorLocation(TargetLocation, false);
			World->GetTimerManager().ClearTimer(MovementTimerHandle);
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
		
		FVector TargetLocationOnSameAxis = TargetLocation - CurrentLocation;
		TargetLocationOnSameAxis.Z = 0.f;
		FRotator NewRotation = FRotationMatrix::MakeFromX(TargetLocationOnSameAxis).Rotator();
		SetActorRotation(NewRotation);
		
	}, 0.01f, true);
}

void ABrainlessCharacter::ToggleMesh(const bool Idle)
{
	BrainlessIdleMesh->SetVisibility(Idle);
	BrainlessWalkMesh->SetVisibility(!Idle);
}
