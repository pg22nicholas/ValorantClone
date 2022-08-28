// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Weapon/WeaponData.h"
#include "ValorantCloneGameModeBase.generated.h"

enum class PLAYABLE_CHARACTERS;
enum class TEAMS;
class AValorantPlayerBase;

namespace InProgressStates
{
	extern const FName NotInProgress;				// State when base GameMode InProgress state not yet reached, or passed			
	extern const FName WaitingLoadingPhase;			// When players are stuck in spot, waiting for all players to load into the map
	extern const FName BuyingPhase;					// When all players are buying their weapons
	extern const FName RoundInProgress;				// When main round is active, all players attacks/shooting usable
	extern const FName EndRound;				// Map and players is resetting after one team won the round, goes back to buying phase
	extern const FName GameEnded;					// When one of the teams have won the the game
}

UCLASS()
class VALORANTCLONE_API AValorantCloneGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AValorantCloneGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 PlayersPerTeam = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 NumRoundsToWin = 4;

	TMap<FString, bool> SpawnMap;

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	
	TSubclassOf<AValorantPlayerBase> GetPlayerCharacterType(PLAYABLE_CHARACTERS character);

	FTransform GetSpawnPoint(TEAMS teams);
	
	void RespawnAllPlayers();

	void PlayerDied(AValorantPlayerBase* ValorantPlayer);

protected:
	virtual void HandleMatchHasStarted() override;
 
	FName InProgressMatchState;
	virtual void SetInProgressMatchState(FName NewInProgressState);

	void OnValorantMatchStateSet();

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TArray<TSubclassOf<AValorantPlayerBase>> PlayerCharacterTypes;

	FTimerHandle BuyPhaseTimerHandle;
	void EndBuyingRound();

	void EndRoundState();
	void GameEndState();
	void BuyPhaseState();
	
};

UENUM()
enum class PLAYABLE_CHARACTERS
{
	PLAYER_1 = 0,
	PLAYER_2 = 1
};

UENUM()
enum class TEAMS
{
	TEAM_A = 0,
	TEAM_B = 1
};
