// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ValorantCloneGameState.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantCloneGameState : public AGameState
{
	GENERATED_BODY()
	
protected:
	uint8 TeamAWins = 0;
	uint8 TeamBWins = 0;
	uint8 Round = 1;

	
	
};
