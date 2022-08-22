// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopScreen.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "player/ValorantPlayerStateBase.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"


void UShopScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized(); 
	
	UWorld* world = GetWorld();

	if (!world) return;

	// Listen to Buy buttons clicks
	BuyPrimaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchasePrimaryWeapon);
	BuySecondaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchaseSecondaryWeapon);
	
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

void UShopScreen::PurchasePrimaryWeapon_Implementation()
{

	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;
	
	if (UWeaponData* SelectedWeapon = PrimaryWeapons->GetSelectedItem<UWeaponData>())
	{
		PlayerController->GetPlayerState<AValorantPlayerStateBase>()->BuyWeapon(SelectedWeapon); 
	}
}

void UShopScreen::PurchaseSecondaryWeapon_Implementation()
{
	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return; 
	
	if (UWeaponData* SelectedWeapon = SecondaryWeapons->GetSelectedItem<UWeaponData>())
	{
		PlayerController->GetPlayerState<AValorantPlayerStateBase>()->BuyWeapon(SelectedWeapon); 
	}
}
