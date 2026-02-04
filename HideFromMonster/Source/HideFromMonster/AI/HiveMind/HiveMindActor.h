// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiveMindActor.generated.h"

class USphereComponent;
DECLARE_LOG_CATEGORY_EXTERN(LogHiveMindActor, Log, All);

class AMonsterCharacter;

UCLASS()
class HIDEFROMMONSTER_API AHiveMindActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHiveMindActor();

protected:
	UFUNCTION()
	void RemoveDestroyedActor(AActor* DestroyedActor);
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "SearchActor")
	UClass* ActorToSearch;
	
	UPROPERTY(EditAnywhere, Category = "SearchActor")
	float SearchRadius = 500.f;
	
	UPROPERTY(VisibleAnywhere, Category = "SearchActor")
	USphereComponent* SphereDetection;
	
	AMonsterCharacter* MonsterChara;
	
private:
	// Reference to the world
	UWorld* World;
	
	// Array that contains the collision for the overlap actors
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	// Array that will contain actor to ignore 
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY()
	TArray<AController*> OverlappingController;
	
	UBillboardComponent* Billboard;
};
