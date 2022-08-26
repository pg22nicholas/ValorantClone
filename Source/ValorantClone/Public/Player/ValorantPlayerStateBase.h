// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "ValorantPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:

	AValorantPlayerStateBase();

	virtual void BeginPlay() override;

	void SetPlayerType(PLAYABLE_CHARACTERS playerType) { PlayerType = playerType; }
	PLAYABLE_CHARACTERS GetPlayerType() { return PlayerType; }
	
	void SetCurrHealth(float NewHealth)
	{
		CurrHealth = NewHealth;
	}
	float GetCurrHealth() const { return CurrHealth; }

	void SetIsStun(bool isStun) { IsStun = isStun; }
	bool GetIsStun() const { return IsStun; }

	float GetMaxHealth() { return MaxHealth; }

	TEAMS Team;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	float CurrHealth;

	UPROPERTY() 
	float MaxHealth = 100.0f;
	
	UPROPERTY(Replicated)
	bool IsStun = false;

	// Type of player class this player state represents
	PLAYABLE_CHARACTERS PlayerType;

	
	
};
