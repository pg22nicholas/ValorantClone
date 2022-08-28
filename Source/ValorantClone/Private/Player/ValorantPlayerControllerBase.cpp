// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerControllerBase.h"

#include "ValorantCloneGameState.h"
#include "ValorantHUD.h"
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
	
	// If no player state, then set new team for player randomly
	AValorantPlayerStateBase* ValoPlayerState = Cast<AValorantPlayerStateBase>(PlayerState);
	if (!ValoPlayerState) return;
	
	if (IsPlayerFirstSpawn)
	{
		ValoPlayerState->Team = IsTeamA ? TEAMS::TEAM_A : TEAMS::TEAM_B;
		// flip-flop team
		IsTeamA = !IsTeamA;
	}

	ValoPlayerState->ResetRoundState();
	
	IsPlayerFirstSpawn = false;
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	FTransform spawnTransform = GameMode->GetSpawnPoint(ValoPlayerState->Team);
	OwningCharacter = Cast<AValorantPlayerBase>(world->SpawnActor(PlayerClassType, &spawnTransform, spawnParams));
	if (OwningCharacter)
	{
		OwningCharacter->SetPlayerState(ValoPlayerState);
		
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


void AValorantPlayerControllerBase::SER_SetupPlayer_Implementation()
{
	UWorld* world = GetWorld();
	if (!world) return;

	AValorantCloneGameModeBase* GameMode = Cast<AValorantCloneGameModeBase>(UGameplayStatics::GetGameMode(world));
	if (!GameMode) return;

	int rand = UKismetMathLibrary::RandomIntegerInRange(0, 1);
	if (rand == 0)
	{
		PlayerClassType = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_2);
	} else
	{
		PlayerClassType = GameMode->GetPlayerCharacterType(PLAYABLE_CHARACTERS::PLAYER_1);
	}
	
	SER_SpawnPlayer();
}

void AValorantPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

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
