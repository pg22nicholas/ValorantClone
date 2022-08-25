// Copyright Epic Games, Inc. All Rights Reserved.


#include "ValorantCloneGameModeBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerControllerBase.h"
#include "player/ValorantPlayerStateBase.h"

AValorantCloneGameModeBase::AValorantCloneGameModeBase()
{
	PlayerControllerClass = AValorantPlayerControllerBase::StaticClass();
	DefaultPawnClass = AValorantPlayerBase::StaticClass();
	PlayerStateClass = AValorantPlayerStateBase::StaticClass();
}

void AValorantCloneGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (AValorantPlayerControllerBase* MyController = Cast<AValorantPlayerControllerBase>(NewPlayer))
	{
		MyController->SER_SpawnPlayer();
		MyController->SetInputMode(FInputModeGameOnly());
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
