// Copyright Epic Games, Inc. All Rights Reserved.


#include "ValorantCloneGameModeBase.h"

#include "EngineUtils.h"
#include "ValorantCloneGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerControllerBase.h"
#include "player/ValorantPlayerStateBase.h"

namespace InProgressStates
{
	const FName NotInProgress = FName(TEXT("NotInProgress"));
	const FName WaitingLoadingPhase = FName(TEXT("WaitingForPlayers"));
	const FName BuyingPhase = FName(TEXT("BuyingPhase"));				
	const FName RoundInProgress = FName(TEXT("RoundInProgress"));			
	const FName EndRound = FName(TEXT("EndRound"));				
	const FName GameEnded = FName(TEXT("GameEnded"));				
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
		MyController->SER_SetupPlayer();
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

void AValorantCloneGameModeBase::RespawnAllPlayers()
{
	UWorld* world = GetWorld();
	if (!world) return;
	
	TArray<AActor*> AllControllers;
	UGameplayStatics::GetAllActorsOfClass(world, AValorantPlayerControllerBase::StaticClass(), AllControllers);
	for (AActor* controllerActor : AllControllers)
	{
		AValorantPlayerControllerBase* controller = Cast<AValorantPlayerControllerBase>(controllerActor);
		if (controller)
		{
			controller->SER_SpawnPlayer();
		}
	}
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

	AValorantCloneGameState* ValoGameState = GetGameState<AValorantCloneGameState>();
	if (ValoGameState)
	{
		ValoGameState->SetInProgressMatchState(NewInProgressState);
	}

	OnValorantMatchStateSet();
}

void AValorantCloneGameModeBase::OnValorantMatchStateSet()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, InProgressMatchState.ToString());
	if (InProgressMatchState == InProgressStates::NotInProgress)
	{
		// TODO?
	} else if (InProgressMatchState == InProgressStates::WaitingLoadingPhase)
	{
		// TODO?
	} else if (InProgressMatchState == InProgressStates::BuyingPhase)
	{
		BuyPhaseState();
		
	} else if (InProgressMatchState == InProgressStates::RoundInProgress)
	{
		// reset PlayerStarts for next round's spawning
		SpawnMap.Empty();
	} else if (InProgressMatchState == InProgressStates::EndRound)
	{
		EndRoundState();
		
	} else if (InProgressMatchState == InProgressStates::GameEnded)
	{
		GameEndState();
	}
}

void AValorantCloneGameModeBase::EndBuyingRound()
{
	SetInProgressMatchState(InProgressStates::RoundInProgress);
}

void AValorantCloneGameModeBase::EndRoundState()
{
	UWorld* world = GetWorld();
	if (!world) return;

	// Check if a team has one after winning last round
	if (AValorantCloneGameState* ValorantGameState = Cast<AValorantCloneGameState>(world->GetGameState()))
	{
		if (ValorantGameState->GetNumTeamAWins() >= NumRoundsToWin ||
				ValorantGameState->GetNumTeamBWins() >= NumRoundsToWin)
		{
			SetInProgressMatchState(InProgressStates::GameEnded);
		}
		// Otherwise, reset round state
		else
		{
			RespawnAllPlayers();
			SetInProgressMatchState(InProgressStates::BuyingPhase);
		}
	}
}

void AValorantCloneGameModeBase::GameEndState()
{
	UWorld* world = GetWorld();
	if (!world) return;

	if (AValorantCloneGameState* ValorantGameState = Cast<AValorantCloneGameState>(world->GetGameState()))
	{
		FString winningTeam = ValorantGameState->GetNumTeamAWins() >= NumRoundsToWin ? "TeamA" : "TeamB";
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Blue, "Team: " + winningTeam);
	}
}

void AValorantCloneGameModeBase::BuyPhaseState()
{
	UWorld* world = GetWorld();
	if (!world) return;

	// set Buy Phase timer until round starts
	world->GetTimerManager().SetTimer(BuyPhaseTimerHandle, this, &AValorantCloneGameModeBase::EndBuyingRound, 10, false);
}

void AValorantCloneGameModeBase::PlayerDied(AValorantPlayerBase* ValorantPlayer)
{
	UWorld* world = GetWorld();
	if (!world) return;

	if (AValorantCloneGameState* ValorantGameState = Cast<AValorantCloneGameState>(world->GetGameState()))
	{
		ValorantGameState->PlayerDied(ValorantPlayer->GetTeam());
		// if all players of a single team dead, end the round 
		if (ValorantGameState->GetNumTeamADead() >= PlayersPerTeam ||
			ValorantGameState->GetNumTeamBDead() >= PlayersPerTeam)
		{
			SetInProgressMatchState(InProgressStates::EndRound);
		} 
	}
}
