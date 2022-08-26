// Fill out your copyright notice in the Description page of Project Settings.


#include "ValorantCloneGameState.h"

#include "Net/UnrealNetwork.h"

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

bool AValorantCloneGameState::IsMatchValorantRestartingMap()
{
	return InProgressMatchState == InProgressStates::RoundRestarting;
}

bool AValorantCloneGameState::IsMatchNotInProgress()
{
	return InProgressMatchState == InProgressStates::NotInProgress;
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
	} else if (InProgressMatchState == InProgressStates::RoundRestarting)
	{
		// TODO:?
	}
}

void AValorantCloneGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantCloneGameState, InProgressMatchState);
	DOREPLIFETIME(AValorantCloneGameState, PlayerCharacters);
}
