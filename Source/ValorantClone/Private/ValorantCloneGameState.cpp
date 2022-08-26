// Fill out your copyright notice in the Description page of Project Settings.


#include "ValorantCloneGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"

void AValorantCloneGameState::SetInProgressMatchState(FName NewInProgressState)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		InProgressMatchState = NewInProgressState;

		// Call the onrep to make sure the callbacks happen
		OnRep_InProgressMatchState();
	}
}

bool AValorantCloneGameState::IsMatchValorantWaitingPlayers()
{
	return InProgressMatchState == InProgressStates::WaitingLoadingPhase;
}

bool AValorantCloneGameState::IsMatchValorantBuying()
{
	return InProgressMatchState == InProgressStates::BuyingPhase;
}

bool AValorantCloneGameState::IsMatchValorantInProgress()
{
	return InProgressMatchState == InProgressStates::RoundInProgress;
}

bool AValorantCloneGameState::IsMatchValorantEndRound()
{
	return InProgressMatchState == InProgressStates::EndRound;
}

bool AValorantCloneGameState::IsMatchValorantNotInProgress()
{
	return InProgressMatchState == InProgressStates::NotInProgress;
}

bool AValorantCloneGameState::IsMatchEnded()
{
	return InProgressMatchState == InProgressStates::GameEnded;
}

void AValorantCloneGameState::PlayerDied(TEAMS team)
{
	if (team == TEAMS::TEAM_A)
	{
		NumTeamADead++;
	} else
	{
		NumTeamBDead++;
	}
}

uint8 AValorantCloneGameState::GetNumTeamADead()
{
	return NumTeamADead;
}

uint8 AValorantCloneGameState::GetNumTeamBDead()
{
	return NumTeamBDead;
}

uint8 AValorantCloneGameState::GetNumTeamAWins()
{
	return TeamAWins;
}

uint8 AValorantCloneGameState::GetNumTeamBWins()
{
	return TeamBWins;
}

void AValorantCloneGameState::EndRound()
{
	UWorld* world = GetWorld();
	if (!world) return;
	
	AValorantCloneGameModeBase* ValoGameMode = Cast<AValorantCloneGameModeBase>(UGameplayStatics::GetGameMode(world));
	if (ValoGameMode)
	{
		if (NumTeamADead >= ValoGameMode->PlayersPerTeam)
		{
			TeamBWins++;
		} else if (NumTeamBDead >= ValoGameMode->PlayersPerTeam)
		{
			TeamAWins++;
		}
	}
	Round++;
	ResetRoundState();
}

void AValorantCloneGameState::ResetRoundState()
{
	NumTeamADead = 0;
	NumTeamBDead = 0;
}


void AValorantCloneGameState::OnRep_InProgressMatchState()
{
	if (InProgressMatchState == InProgressStates::NotInProgress)
	{
		// TODO?
	}
	else if (InProgressMatchState == InProgressStates::WaitingLoadingPhase)
	{
		// TODO:?
	} else if (InProgressMatchState == InProgressStates::BuyingPhase)
	{
		// TODO:?
	} else if (InProgressMatchState == InProgressStates::RoundInProgress)
	{
		// TODO:?
	} else if (InProgressMatchState == InProgressStates::EndRound)
	{
		EndRound();
	} else if (InProgressMatchState == InProgressStates::GameEnded)
	{
		// TODO?
	}
}

void AValorantCloneGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantCloneGameState, InProgressMatchState);
	DOREPLIFETIME(AValorantCloneGameState, PlayerCharacters);
}
