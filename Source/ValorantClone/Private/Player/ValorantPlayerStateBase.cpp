// Fill out your copyright notice in the Description page of Project Settings.

#include "player/ValorantPlayerStateBase.h"
#include "DamageTypes/BaseDamageType.h"

#include "Net/UnrealNetwork.h"

AValorantPlayerStateBase::AValorantPlayerStateBase()
{
	PlayerType = PLAYABLE_CHARACTERS::PLAYER_1;
}

void AValorantPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();
	CurrHealth = MaxHealth;
}


void AValorantPlayerStateBase::ResetRoundState()
{
	CurrHealth = MaxHealth;
	IsStun = false;
}

void AValorantPlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerStateBase, CurrHealth);
}
