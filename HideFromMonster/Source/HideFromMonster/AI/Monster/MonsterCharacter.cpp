// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"

#include "MonsterController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HideFromMonster/AI/HiveMind/HiveMindActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Note : Some of this settings might not be change in a realistic production due to the lack of knowledge about 
	// the monster mesh and characteristic

	// Apply specific data to the movement of the monster
	if (UCharacterMovementComponent* CharaMovement = GetCharacterMovement())
	{
		CharaMovement->MaxWalkSpeed = 200.0f;

		// Make sure the controller as full control of the character rotation
		CharaMovement->bUseControllerDesiredRotation = true;
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

	SphereCompo = CreateDefaultSubobject<USphereComponent>(TEXT("Hive Mind Sphere Compo"));

	if (UCapsuleComponent* CapsuleCompo = GetCapsuleComponent())
		SphereCompo->SetupAttachment(CapsuleCompo);
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Binding and initialization of the Sphere for the collision 
	if (const UWorld* World = GetWorld())
	{
		HiveMindActor = Cast<AHiveMindActor>(UGameplayStatics::GetActorOfClass(World, AHiveMindActor::StaticClass()));
		
		if (HiveMindActor)
		{
			SphereCompo->SetSphereRadius(HiveMindActor->SearchRadius);
			
			SphereCompo->OnComponentBeginOverlap.AddDynamic(this, &AMonsterCharacter::OnBeginOverLap);
			SphereCompo->OnComponentEndOverlap.AddDynamic(this, &AMonsterCharacter::OnEndOverlap);
		}
	}
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

void AMonsterCharacter::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HiveMindActor)
		HiveMindActor->AddCloseController(OtherActor);
}

void AMonsterCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HiveMindActor)
		HiveMindActor->RemoveCloseController(OtherActor);
}
