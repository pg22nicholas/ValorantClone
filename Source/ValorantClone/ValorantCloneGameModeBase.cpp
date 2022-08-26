// Copyright Epic Games, Inc. All Rights Reserved.


#include "ValorantCloneGameModeBase.h"

#include "EngineUtils.h"
#include "ValorantCloneGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerControllerBase.h"
#include "player/ValorantPlayerStateBase.h"

namespace InProgressStates
{
	const FName NotInProgress = FName(TEXT("NotInProgress"));
	const FName WaitingLoadingPhase = FName(TEXT("WaitingForPlayers"));
	const FName BuyingPhase = FName(TEXT("BuyingPhase"));				
	const FName RoundInProgress = FName(TEXT("RoundInProgress"));			
	const FName RoundRestarting = FName(TEXT("RoundRestarting"));				
}


AValorantCloneGameModeBase::AValorantCloneGameModeBase()
{
	PlayerControllerClass = AValorantPlayerControllerBase::StaticClass();
	DefaultPawnClass = AValorantPlayerBase::StaticClass();
	PlayerStateClass = AValorantPlayerStateBase::StaticClass();
}

void AValorantCloneGameModeBase::BeginPlay()
{

	Super::BeginPlay();
	InProgressMatchState = InProgressStates::NotInProgress;
}

void AValorantCloneGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UWorld* world = GetWorld();
	if (!world) return;
	
	if (AValorantPlayerControllerBase* MyController = Cast<AValorantPlayerControllerBase>(NewPlayer))
	{
		MyController->SER_SpawnPlayer();
		MyController->SetInputMode(FInputModeGameOnly());

		// check if all players loaded in
		if (AValorantCloneGameState* ValorantGameState = Cast<AValorantCloneGameState>(world->GetGameState()))
		{
			if (ValorantGameState->PlayerCharacters.Num() == PlayersPerTeam * 2)
			{
				if (InProgressMatchState == InProgressStates::WaitingLoadingPhase)
				{
					SetInProgressMatchState(InProgressStates::BuyingPhase);
				}
			}
		}
	}
}

TSubclassOf<AValorantPlayerBase> AValorantCloneGameModeBase::GetPlayerCharacterType(PLAYABLE_CHARACTERS character)
{
	return PlayerCharacterTypes[static_cast<uint8>(character)];
}

FTransform AValorantCloneGameModeBase::GetSpawnPoint(TEAMS team)
{
	for (TActorIterator<APlayerStart> playerStart(GetWorld()); playerStart; ++playerStart)
	{
		// TODO: Use tags to prevent spawning multiple players at same spot and use teams parameter
		FName name = team == TEAMS::TEAM_A ? "TeamA" : "TeamB";
		if (!SpawnMap.Find(playerStart->GetName()) && playerStart->PlayerStartTag == name)
		{
			SpawnMap.Add(playerStart->GetName(), true);
			return playerStart->GetTransform();
		}
	}
	return FTransform();
}

void AValorantCloneGameModeBase::HandleMatchHasStarted()
{

	Super::HandleMatchHasStarted();
	SetInProgressMatchState(InProgressStates::WaitingLoadingPhase);
}
 
void AValorantCloneGameModeBase::SetInProgressMatchState(FName NewInProgressState)
{
	if (InProgressMatchState == NewInProgressState)
	{
		return;
	}
	
	InProgressMatchState = NewInProgressState;

	OnValorantMatchStateSet();

	AValorantCloneGameState* ValoGameState = GetGameState<AValorantCloneGameState>();
	if (ValoGameState)
	{
		ValoGameState->SetInProgressMatchState(NewInProgressState);
	}
}

void AValorantCloneGameModeBase::OnValorantMatchStateSet()
{
	if (InProgressMatchState == InProgressStates::NotInProgress)
	{
		// TODO?
	}
	else if (InProgressMatchState == InProgressStates::WaitingLoadingPhase)
	{
		// TODO?
	} else if (InProgressMatchState == InProgressStates::BuyingPhase)
	{
		// TODO?
	} else if (InProgressMatchState == InProgressStates::RoundInProgress)
	{
		// TODO?
	} else if (InProgressMatchState == InProgressStates::RoundRestarting)
	{
		// TODO?
	}
}
