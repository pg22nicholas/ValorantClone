// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageTypes/BaseDamageType.h"
#include "player/ValorantPlayerStateBase.h"

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


void AValorantPlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerStateBase, CurrHealth);
}
