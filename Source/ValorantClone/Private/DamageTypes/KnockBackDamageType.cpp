// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/KnockBackDamageType.h"

float UKnockBackDamageType::ProcessDamage(AActor* Owner, AValorantPlayerBase* HitCharacter, FVector HitLocation) const
{
	if (const IDamagingInterface* DamageInterface = Cast<IDamagingInterface>(HitCharacter))
	{
		FVector direction = HitCharacter->GetActorLocation() - HitLocation;
		direction.Normalize();
		direction *= KnockBackForce;
		direction.Z = KnockUpForce;
		DamageInterface->Execute_KnockBack(HitCharacter, direction);
	}
	return DamageMultiplier;
}