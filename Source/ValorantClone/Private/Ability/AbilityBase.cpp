// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityBase.h"

AAbilityBase::AAbilityBase()
{
	bReplicates = true;
}

// Add default functionality here for any IAbilityInterface functions that are not pure virtual.
bool AAbilityBase::BeforeAbility(APlayerController* controller)
{
	if (bOnCooldown) return false;
	CachedPlayerController = MakeWeakObjectPtr(controller);
	TimeOnHoldStart = GetGameTimeSinceCreation();
	IsHolding = true;
	return true;
}

bool AAbilityBase::PerformAbility()
{
	if (bOnCooldown) return false;

	if (IsHoldAbility && !IsHolding) return false;
	IsHolding = false;

	UWorld* world = GetWorld();
	if (!world) return false;

	world->GetTimerManager().SetTimer(CooldownTimerHandle, this, &AAbilityBase::CooldownFinished, Cooldown, false);
	bOnCooldown = true;
	return true;
}

void AAbilityBase::CooldownFinished()
{
	bOnCooldown = false;
}
