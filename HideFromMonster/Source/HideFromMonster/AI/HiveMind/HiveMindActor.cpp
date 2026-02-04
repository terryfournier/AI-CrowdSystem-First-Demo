// Fill out your copyright notice in the Description page of Project Settings.


#include "HiveMindActor.h"

#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "HideFromMonster/AI/Monster/MonsterCharacter.h"
#include "HideFromMonster/Interface/LaunchQueryInterface.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogHiveMindActor);

// Sets default values
AHiveMindActor::AHiveMindActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Billboard = CreateDefaultSubobject<UBillboardComponent>(FName("Billboard"));
	
	RootComponent = Billboard;
	
	SphereDetection = CreateDefaultSubobject<USphereComponent>(FName("SphereDetection"));
	SphereDetection->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHiveMindActor::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

	if (World)
	{
		// Get the monster character to lauch the overlap
		MonsterChara = Cast<AMonsterCharacter>(UGameplayStatics::GetActorOfClass(World,
			AMonsterCharacter::StaticClass()));
		
		SphereDetection->SetSphereRadius(SearchRadius);
		SphereDetection->SetWorldLocation(MonsterChara->GetActorLocation(), true);
		
		SphereDetection->OnComponentBeginOverlap.AddDynamic(this, &AHiveMindActor::OnBeginOverlap);
		SphereDetection->OnComponentEndOverlap.AddDynamic(this, &AHiveMindActor::OnEndOverlap);
	}
}

// Called every frame
void AHiveMindActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereDetection->SetWorldLocation(MonsterChara->GetActorLocation(), true);
	
	for (AController* Controller : OverlappingController)
	{
		ILaunchQueryInterface::Execute_LaunchQuery(Controller);
		/*const UObject* ControllerObject = Cast<UObject>(Controller);
		if (ControllerObject && !ControllerObject->IsUnreachable())
		{
			if (Controller && Controller->GetClass()->ImplementsInterface(ULaunchQueryInterface::StaticClass()))
			{
				
			}
			else
			{
				
			}
		}*/
	}
}

void AHiveMindActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappingController.Add(OtherActor->GetInstigatorController());
	OtherActor->OnDestroyed.AddDynamic(this, &AHiveMindActor::RemoveDestroyedActor);
	DrawDebugSphere(GetWorld(), OtherActor->GetActorLocation(), 20, 20, FColor::Red);
}

void AHiveMindActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingController.Remove(OtherActor->GetInstigatorController());
}

void AHiveMindActor::RemoveDestroyedActor(AActor* DestroyedActor)
{
	OverlappingController.Remove(DestroyedActor->GetInstigatorController());
}
