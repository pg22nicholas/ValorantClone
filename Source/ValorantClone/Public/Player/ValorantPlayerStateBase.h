// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "ValorantPlayerStateBase.generated.h"

/**
 * 
 */
class UWeaponData; 

UCLASS(BlueprintType) 
class VALORANTCLONE_API AValorantPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:

	AValorantPlayerStateBase();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Max_Health = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)  
	float CurHealth = 100; 
	
	
	void SetPlayerType(PLAYABLE_CHARACTERS playerType) { PlayerType = playerType; }
	PLAYABLE_CHARACTERS GetPlayerType() { return PlayerType; }


	
private:
	
	// Type of player class this player state represents
	PLAYABLE_CHARACTERS PlayerType;

	virtual void BeginPlay() override;

	
};
