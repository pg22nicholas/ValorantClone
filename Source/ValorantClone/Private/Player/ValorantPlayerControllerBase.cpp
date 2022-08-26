// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerControllerBase.h"

#include "ValorantCloneGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerStateBase.h"

void AValorantPlayerControllerBase::SER_SpawnPlayer_Implementation()
{
	UWorld* world = GetWorld();
	if (!world) return;

	AValorantCloneGameModeBase* GameMode = Cast<AValorantCloneGameModeBase>(UGameplayStatics::GetGameMode(world));
	if (!GameMode) return;

	

	// TODO: use player state player type instead ***
	TSubclassOf<AValorantPlayerBase> PlayerCharacter;

	int rand = UKismetMathLibrary::RandomIntegerInRange(0, 1);
	if (rand == 0)
	{
		PlayerCharacter = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_2);
	} else
	{
		PlayerCharacter = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_1);
	}

	TEAMS team = IsTeamA ? TEAMS::TEAM_A : TEAMS::TEAM_B;
	// flip-flop team
	IsTeamA = !IsTeamA;
	
	//TSubclassOf<AValorantPlayerBase> PlayerCharacter = GameMode->GetPlayerCharacterType(MyPlayerState->GetPlayerType());

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	FTransform spawnTransform = GameMode->GetSpawnPoint(team);
	OwningCharacter = Cast<AValorantPlayerBase>(world->SpawnActor(PlayerCharacter, &spawnTransform, spawnParams));
	if (OwningCharacter)
	{
		OwningCharacter->SetTeam(team);
		
		APawn* CachedPawn = GetPawn();
		Possess(OwningCharacter);

		if (AValorantCloneGameState* ValorantGameState = Cast<AValorantCloneGameState>(world->GetGameState()))
		{
			ValorantGameState->PlayerCharacters.AddUnique(OwningCharacter);
		}
		
		if (CachedPawn != nullptr)
			CachedPawn->Destroy();
	}
}


