// Fill out your copyright notice in the Description page of Project Settings.


#include "HiveMindActor.h"
#include "Components/BillboardComponent.h"
#include "HideFromMonster/Interface/LaunchQueryInterface.h"

DEFINE_LOG_CATEGORY(LogHiveMindActor);

// Sets default values
AHiveMindActor::AHiveMindActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(FName("Billboard"));

	RootComponent = Billboard;
}

// Called when the game starts or when spawned
void AHiveMindActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHiveMindActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*for (AController* Controller : OverlappingController)
	{
		// Launching query for the controller that are to close of the monster
		if (Controller)
			ILaunchQueryInterface::Execute_LaunchQuery(Controller);
	}*/
}

void AHiveMindActor::AddCloseController(AActor* OtherActor)
{
	// Adding the controller to the array and binding Remove to the OnDestroy function
	AController* ActorController = OtherActor->GetInstigatorController();
	if (!ActorController)
		return;
	
	OverlappingController.Add(ActorController);
	OtherActor->OnDestroyed.AddDynamic(this, &AHiveMindActor::RemoveCloseController);
	LaunchQuery(ActorController);
}

void AHiveMindActor::RemoveCloseController(AActor* OtherActor)
{
	// Removing and Unbind the function to OnDestroy
	OverlappingController.Remove(OtherActor->GetInstigatorController());
	OtherActor->OnDestroyed.RemoveDynamic(this, &AHiveMindActor::RemoveCloseController);
}

// If the controller is ovelapping than the query will be launch on this controller
void AHiveMindActor::LaunchQuery(AController* ControllerQueryHandler)
{
	if (OverlappingController.Contains(ControllerQueryHandler))
		ILaunchQueryInterface::Execute_LaunchQuery(ControllerQueryHandler);
}
