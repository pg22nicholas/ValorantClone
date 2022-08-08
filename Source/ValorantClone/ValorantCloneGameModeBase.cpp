// Copyright Epic Games, Inc. All Rights Reserved.


#include "ValorantCloneGameModeBase.h"

#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerControllerBase.h"
#include "player/ValorantPlayerStateBase.h"

AValorantCloneGameModeBase::AValorantCloneGameModeBase()
{
	PlayerControllerClass = AValorantPlayerControllerBase::StaticClass();
	DefaultPawnClass = AValorantPlayerBase::StaticClass();
	PlayerStateClass = AValorantPlayerStateBase::StaticClass();
}
