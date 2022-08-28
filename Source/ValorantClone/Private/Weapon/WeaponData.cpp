// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponData.h"

#include "Net/UnrealNetwork.h"


void UWeaponData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponData, WeaponPrice);
	DOREPLIFETIME(UWeaponData, WeaponName); 
}
