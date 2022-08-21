// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerStateBase.h"

AValorantPlayerStateBase::AValorantPlayerStateBase()
{
	CurrHealth = Health;

	PlayerType = PLAYABLE_CHARACTERS::PLAYER_1;
}

void AValorantPlayerStateBase::BuyWeapon_Implementation(UWeaponData* Weapon)
{
    // Mo Money case:
	if (Money < Weapon->WeaponPrice)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Not Enough Money");
		return;  
	}

	// Already owned:
    for (auto OwnedWeapon : OwnedWeapons) 
    {
	    if (OwnedWeapon == Weapon)
	    {
	    	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Exists"); 
		    return;
	    }
    }
	
	// Money decrement
	Money-=Weapon->WeaponPrice;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Purchased"); 


	// Add Weapon to collection
	OwnedWeapons.Add(Weapon);

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Added");

}




