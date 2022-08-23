// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/StunDamageType.h"

float UStunDamageType::ProcessDamage(AActor* Owner, AValorantPlayerBase* HitCharacter, FVector HitLocation) const
{
	if (const IDamagingInterface* DamageInterface = Cast<IDamagingInterface>(HitCharacter))
	{
		DamageInterface->Execute_Stun(HitCharacter, StunDuration);
	}
	return DamageMultiplier;
}
