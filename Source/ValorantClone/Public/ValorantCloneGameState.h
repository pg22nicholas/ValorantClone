// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ValorantCloneGameState.generated.h"

class AValorantPlayerBase;
enum class TEAMS;

namespace ValorantMatchState
{
	extern ENGINE_API const FName EnteringMap;			// We are entering this map, actors are not yet ticking
	extern ENGINE_API const FName WaitingToStart;		// Actors are ticking, but the match has not yet started
	extern ENGINE_API const FName InProgress;			// Normal gameplay is occurring. Specific games will have their own state machine inside this state
	extern ENGINE_API const FName WaitingPostMatch;		// Match has ended so we aren't accepting new players, but actors are still ticking
	extern ENGINE_API const FName LeavingMap;			// We are transitioning out of the map to another location
	extern ENGINE_API const FName Aborted;				// Match has failed due to network issues or other problems, cannot continue

	// If a game needs to add additional states, you may need to override HasMatchStarted and HasMatchEnded to deal with the new states
	// Do not add any states before WaitingToStart or after WaitingPostMatch
}

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantCloneGameState : public AGameState
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated)
	TArray<AValorantPlayerBase*> PlayerCharacters;

	virtual void SetInProgressMatchState(FName NewInProgressState);

	// getters for player characters to check the state of the game
	bool IsMatchValorantWaitingPlayers();
	bool IsMatchValorantBuying();
	bool IsMatchValorantInProgress();
	bool IsMatchValorantEndRound();
	bool IsMatchValorantNotInProgress();
	bool IsMatchEnded();

	void PlayerDied(TEAMS team);

	uint8 GetNumTeamADead();
	uint8 GetNumTeamBDead();

	uint8 GetNumTeamAWins();
	uint8 GetNumTeamBWins();
	
protected:
	uint8 TeamAWins = 0;
	uint8 TeamBWins = 0;
	uint8 Round = 1;

	UPROPERTY(ReplicatedUsing=OnRep_InProgressMatchState, BlueprintReadOnly, VisibleInstanceOnly, Category = GameState)
	FName InProgressMatchState;

	UFUNCTION()
	virtual void OnRep_InProgressMatchState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	uint8 NumTeamADead = 0;
	uint8 NumTeamBDead = 0;

	void EndRound();
	void ResetRoundState();
	
};
