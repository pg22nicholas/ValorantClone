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

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;; 
	
	if (!ShopScreen) 
	{
		// OPEN LOGIC
		
		ShopScreen = CreateWidget<UShopScreen>(GetOwningPlayerController(), ShopScreenClass, TEXT ("STORE"));

		ShopScreen->AddToViewport(10);

		PlayerController->bShowMouseCursor = true; 
	}
	else
	{
		PlayerController->bShowMouseCursor = false;
		
		ShopScreen->RemoveFromParent(); 

		ShopScreen = nullptr; 
	}
}

