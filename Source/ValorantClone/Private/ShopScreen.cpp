// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopScreen.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"


void UShopScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized(); 
	
	SetupStore();  
}

void UShopScreen::SetupStore() 
{ 
	UWorld* world = GetWorld();

	if (!world) return;

	// Listen to Buy buttons clicks
	BuyPrimaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchasePrimaryWeapon);
	BuySecondaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchaseSecondaryWeapon);
	
	if (AValorantCloneGameModeBase* gameMode = world->GetAuthGameMode<AValorantCloneGameModeBase>())
	{
		 
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

		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald, FString::FromInt(PrimaryWeaponList.Num())); 
	} 
}

void UShopScreen::PurchasePrimaryWeapon_Implementation()
{

	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;

	AValorantPlayerBase* PlayerBase = PlayerController->GetPawn<AValorantPlayerBase>();
	if (!PlayerBase) return;
	
	if (UWeaponData* SelectedWeapon = PrimaryWeapons->GetSelectedItem<UWeaponData>())
	{
		PlayerBase->BuyWeapon(SelectedWeapon);
	}
}

void UShopScreen::PurchaseSecondaryWeapon_Implementation()
{
	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;

	AValorantPlayerBase* PlayerBase = PlayerController->GetPawn<AValorantPlayerBase>();
	if (!PlayerBase) return;
	
	if (UWeaponData* SelectedWeapon = SecondaryWeapons->GetSelectedItem<UWeaponData>())
	{
		PlayerBase->BuyWeapon(SelectedWeapon); 
	}
}
