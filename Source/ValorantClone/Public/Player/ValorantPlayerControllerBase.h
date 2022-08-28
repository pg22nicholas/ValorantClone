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

	UFUNCTION(Server, Reliable)
	void SER_SetupPlayer(); 

	TSubclassOf<AValorantPlayerBase> PlayerClassType;

	virtual void SetupInputComponent() override;

	UFUNCTION() 
	void ToggleStore();

private:

	UPROPERTY()
	AValorantPlayerBase* OwningCharacter;

	bool IsPlayerFirstSpawn = true;
	
};

static bool IsTeamA = true;
