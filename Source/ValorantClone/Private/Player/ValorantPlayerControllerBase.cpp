// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerControllerBase.h"

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

	AValorantPlayerStateBase* MyPlayerState = Cast<AValorantPlayerStateBase>(PlayerState);
	if (!PlayerState) return;

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
		
	
	//TSubclassOf<AValorantPlayerBase> PlayerCharacter = GameMode->GetPlayerCharacterType(MyPlayerState->GetPlayerType());

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	FTransform spawnTransform = GameMode->GetSpawnPoint(TEAMS::TEAM_A);
	OwningCharacter = Cast<AValorantPlayerBase>(world->SpawnActor(PlayerCharacter, &spawnTransform, spawnParams));
	if (OwningCharacter)
	{
		APawn* CachedPawn = GetPawn();
		Possess(OwningCharacter);
		
		if (CachedPawn != nullptr)
			CachedPawn->Destroy();
	}
}
