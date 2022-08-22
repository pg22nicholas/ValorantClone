// Fill out your copyright notice in the Description page of Project Settings.


#include "player/ValorantPlayerStateBase.h"

#include "Weapon/WeaponBase.h"

AValorantPlayerStateBase::AValorantPlayerStateBase()
{
	CurHealth = Max_Health;

	PlayerType = PLAYABLE_CHARACTERS::PLAYER_1;
}

void AValorantPlayerStateBase::SwitchWeapon_Implementation()
{
	const int& ListLength =  OwnedWeapons.Num();
	if (ListLength <= 1 ) return;
	
    for (int i = 0; i < ListLength; i++)
    {
	    if (OwnedWeapons[i] == CurrentWeapon)
	    {
		    if (i+1 < ListLength) 
		    {
			    CurrentWeapon = OwnedWeapons[i+1];
		    	return;
		    }
	    	else
	    	{
	    		CurrentWeapon =  OwnedWeapons[0];
	    		return;
	    	}
	    }
    	
    }
	
}

void AValorantPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	AValorantPlayerBase * PlayerBase = GetPawn<AValorantPlayerBase>();
	if (!PlayerBase) return;

	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(PlayerBase->Weapon->GetChildActor())) 
	{
		if (!weaponBase->WeaponData) return; 
		
		OwnedWeapons.Add(weaponBase->WeaponData);   
	}
	
	if (OwnedWeapons.Num() > 0) 
	{
		CurrentWeapon = OwnedWeapons[0];  
	}
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
	
	PurchaseDelegate.Broadcast(Money); // Hud update delegate
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Purchased"); 


	// Add Weapon to collection
	OwnedWeapons.Add(Weapon);

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Added");

}




