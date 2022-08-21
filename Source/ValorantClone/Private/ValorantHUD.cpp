// Fill out your copyright notice in the Description page of Project Settings.


#include "ValorantHUD.h"
#include "ShopScreen.h" 

#include "Blueprint/UserWidget.h"
#include "Weapon/WeaponBase.h"


AValorantHUD::AValorantHUD() 
{

}

void AValorantHUD::DrawHUD()
{
	Super::DrawHUD();


}

void AValorantHUD::ToggleStore()
{
	UWorld * world = GetWorld();
	if (!world) return;

	if (!ShopScreen) 
	{
		// OPEN LOGIC
		
		ShopScreen = CreateWidget<UShopScreen>(GetOwningPlayerController(), ShopScreenClass, TEXT ("STORE"));

		ShopScreen->AddToViewport(10); 
	}
	else
	{
		ShopScreen->RemoveFromParent(); 

		ShopScreen = nullptr; 
	}
}

