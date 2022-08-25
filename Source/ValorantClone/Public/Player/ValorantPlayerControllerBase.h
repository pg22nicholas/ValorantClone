// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValorantPlayerBase.h"
#include "GameFramework/PlayerController.h"
#include "ValorantPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	
	
	UFUNCTION(Server, Reliable)
	void SER_SpawnPlayer();

private:

	UPROPERTY()
	AValorantPlayerBase* OwningCharacter;
	
};

static bool IsTeamA = true;
