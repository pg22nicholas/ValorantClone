// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopScreen.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "ValorantClone/Public/Weapon/WeaponBase.h" 


void UShopScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized(); 

	UWorld* world = GetWorld();

	if (!world) return;

	
	if (AValorantCloneGameModeBase* gameMode = world->GetAuthGameMode<AValorantCloneGameModeBase>())
	{
		int32 lol = gameMode->AllWeapons.Num();

		TArray<UWeaponData*> PrimaryWeaponList; 
		TArray<UWeaponData*> SecondaryWeaponList; 

		PrimaryWeaponList = gameMode->AllWeapons.FilterByPredicate([](const UWeaponData* Weapon) -> bool
						{
							return Weapon->PrimaryWeapon;
						});
		SecondaryWeaponList = gameMode->AllWeapons.FilterByPredicate([](const UWeaponData* Weapon) -> bool
						{
							return !Weapon->PrimaryWeapon;   
						});
		
		PrimaryWeapons->SetListItems<UWeaponData*>(PrimaryWeaponList);   

		SecondaryWeapons->SetListItems<UWeaponData*>(SecondaryWeaponList);  
	} 

	
}
