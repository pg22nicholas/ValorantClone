// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityBase.h"

AAbilityBase::AAbilityBase()
{
	bReplicates = true;
}

// Add default functionality here for any IAbilityInterface functions that are not pure virtual.
void AAbilityBase::StartAbility(APlayerController* controller)
{
	CachedPlayerController = MakeWeakObjectPtr(controller);
}
