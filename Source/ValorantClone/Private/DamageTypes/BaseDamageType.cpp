// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/BaseDamageType.h"

float UBaseDamageType::ProcessDamage(AActor* Owner, APawn* HitCharacter, FVector HitLocation) const
{
	return DamageMultiplier;
}
