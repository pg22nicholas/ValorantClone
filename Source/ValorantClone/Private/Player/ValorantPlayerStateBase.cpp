// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerStateBase.h"


AValorantPlayerStateBase::AValorantPlayerStateBase()
{
	CurHealth = Max_Health;

	PlayerType = PLAYABLE_CHARACTERS::PLAYER_1;
}


void AValorantPlayerStateBase::BeginPlay()
{
	
	Super::BeginPlay();
	
}

