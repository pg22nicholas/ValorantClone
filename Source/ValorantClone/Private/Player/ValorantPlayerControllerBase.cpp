// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerControllerBase.h"
#include "ValorantHUD.h"
#include "Kismet/GameplayStatics.h"
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
	if (IsLocalController())
		PlayerCharacter = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_2);
	else
		PlayerCharacter = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_1);
	
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

void AValorantPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	UWorld * world = GetWorld();
	if (!world) return;
	 
	InputComponent->BindAction("Store", IE_Pressed, this, &AValorantPlayerControllerBase::ToggleStore );
	
}

void AValorantPlayerControllerBase::ToggleStore()
{
	if (AValorantHUD * hud = GetHUD<AValorantHUD>()) 
	{
		hud->ToggleStore();
	}
}
