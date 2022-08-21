// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Player/ValorantPlayerBase.h"
#include "Weapon/WeaponData.h" 
#include "ValorantCloneGameModeBase.generated.h"

class UWeaponData; 

enum class TEAMS;
enum class PLAYABLE_CHARACTERS;
/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantCloneGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AValorantCloneGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	TSubclassOf<AValorantPlayerBase> GetPlayerCharacterType(PLAYABLE_CHARACTERS character);

	FTransform GetSpawnPoint(TEAMS teams) const;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))  
	TArray<UWeaponData*> AllWeapons;   
private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TArray<TSubclassOf<AValorantPlayerBase>> PlayerCharacterTypes;
	
};

enum class PLAYABLE_CHARACTERS
{
	PLAYER_1 = 0,
	PLAYER_2 = 1
};

enum class TEAMS
{
	TEAM_A = 0,
	TEAM_B = 1
};
