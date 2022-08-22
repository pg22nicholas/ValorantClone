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
	if (!PrimaryWeapon && SecondaryWeapon) return;
	
	if (PrimaryWeapon == CurrentWeapon)
	{
		CurrentWeapon = SecondaryWeapon;
	}
	else CurrentWeapon = PrimaryWeapon;
		

	
	
	
}

void AValorantPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	AValorantPlayerBase * PlayerBase = GetPawn<AValorantPlayerBase>();
	if (!PlayerBase) return;

	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(PlayerBase->Weapon->GetChildActor())) 
	{
		if (!weaponBase->WeaponData) return; 
		
		if (weaponBase->WeaponData->PrimaryWeapon)
		{
			PrimaryWeapon = weaponBase->WeaponData;
		}
		else SecondaryWeapon = weaponBase->WeaponData;
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

	
	
    if (PrimaryWeapon == Weapon || SecondaryWeapon == Weapon)
    {
	    GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Exists"); 
	    return;
    }
    
	
	// Money decrement
	Money-=Weapon->WeaponPrice;
	
	PurchaseDelegate.Broadcast(Money); // Hud update delegate
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Purchased"); 



	if (AValorantPlayerBase* PlayerBase =  GetPawn<AValorantPlayerBase>())
	{
		// Equip Purchased Weapon 
		if (AWeaponBase* weaponBase = Cast<AWeaponBase>(PlayerBase->Weapon->GetChildActor())) 
		{
			weaponBase->WeaponData = Weapon; 
		}
		
		// Drop Previous Weapon
		// Add Weapon to collection
		if (Weapon->PrimaryWeapon)
		{
			if (PrimaryWeapon)
				PlayerBase->DropWeapon(PrimaryWeapon);
			PrimaryWeapon = Weapon;
		}
		else
		{
			if (SecondaryWeapon)
				PlayerBase->DropWeapon(SecondaryWeapon); 
			SecondaryWeapon = Weapon;
		}
	}

	

	

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Added");

}




