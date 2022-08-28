// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopScreen.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Net/UnrealNetwork.h"
#include "Player/ValorantPlayerBase.h"
#include "player/ValorantPlayerControllerBase.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "Weapon/WeaponData.h"


void UShopScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized(); 
	
	SetupStore();  
}


void UShopScreen::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UShopScreen, PrimaryWeapons); 
	DOREPLIFETIME(UShopScreen, SecondaryWeapons); 
}

void UShopScreen::SetupStore_Implementation()   
{ 
	UWorld* world = GetWorld();
 
	if (!world) return;

	// Listen to Buy buttons clicks
	BuyPrimaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchasePrimaryWeapon);
	BuySecondaryWeaponButton->OnClicked.AddDynamic(this, &UShopScreen::PurchaseSecondaryWeapon);
	
	if (AValorantCloneGameState* gameState = world->GetGameState<AValorantCloneGameState>())
	{
		 
		TArray<UWeaponData*> PrimaryWeaponList; 
		TArray<UWeaponData*> SecondaryWeaponList; 

		PrimaryWeaponList = gameState->AllWeapons.FilterByPredicate([](const UWeaponData* Weapon) -> bool
						{
							return Weapon->PrimaryWeapon;
						});
		SecondaryWeaponList = gameState->AllWeapons.FilterByPredicate([](const UWeaponData* Weapon) -> bool
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
	UWorld * world = GetWorld()->GetWorld();

	if (!world) return;

	AValorantPlayerControllerBase* ValorantController = world->GetFirstPlayerController<AValorantPlayerControllerBase>();
	if (!ValorantController) return;

	AValorantPlayerBase* ValorantPlayer  = ValorantController->GetPawn<AValorantPlayerBase>(); 
	if (!ValorantPlayer) return;

	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Orange, "PURCHASE FROM SHOPSCREEN");  
	
	if (UWeaponData* SelectedWeapon = PrimaryWeapons->GetSelectedItem<UWeaponData>())
	{
		ValorantPlayer->BuyWeapon(SelectedWeapon);
	}
}

void UShopScreen::PurchaseSecondaryWeapon_Implementation()
{
	
	UWorld * world = GetWorld()->GetWorld();

	if (!world) return;

	AValorantPlayerControllerBase* ValorantController = world->GetFirstPlayerController<AValorantPlayerControllerBase>();
	if (!ValorantController) return;

	AValorantPlayerBase* ValorantPlayer  = ValorantController->GetPawn<AValorantPlayerBase>(); 
	if (!ValorantPlayer) return;

	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Orange, "PURCHASE FROM SHOPSCREEN");  
	
	if (UWeaponData* SelectedWeapon = SecondaryWeapons->GetSelectedItem<UWeaponData>())
	{
		ValorantPlayer->BuyWeapon(SelectedWeapon); 
	}
}
