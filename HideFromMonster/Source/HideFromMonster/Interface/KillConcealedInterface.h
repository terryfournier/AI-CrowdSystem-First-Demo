// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KillConcealedInterface.generated.h"

// This class does not need to be modified.

// Interface to launch to kill the concealed, that way it can be killed by the monster
UINTERFACE(MinimalAPI)
class UKillConcealedInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HIDEFROMMONSTER_API IKillConcealedInterface
{
	GENERATED_BODY()
	
	// function that need to be overridden to implements the kill behavior
	virtual void KilledConcealed() = 0;
public:
};
