// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ValorantCloneGameModeBase.generated.h"

enum class PLAYABLE_CHARACTERS;
enum class TEAMS;
class AValorantPlayerBase;

UCLASS()
class VALORANTCLONE_API AValorantCloneGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AValorantCloneGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	TSubclassOf<AValorantPlayerBase> GetPlayerCharacterType(PLAYABLE_CHARACTERS character);

	FTransform GetSpawnPoint(TEAMS teams);
	
	TMap<FString, bool> SpawnMap;

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TArray<TSubclassOf<AValorantPlayerBase>> PlayerCharacterTypes;

	
};

UENUM()
enum class PLAYABLE_CHARACTERS
{
	PLAYER_1 = 0,
	PLAYER_2 = 1
};

UENUM()
enum class TEAMS
{
	TEAM_A = 0,
	TEAM_B = 1
};
