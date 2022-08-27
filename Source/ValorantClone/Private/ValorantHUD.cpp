// Fill out your copyright notice in the Description page of Project Settings.


#include "ValorantHUD.h"
#include "ShopScreen.h" 
#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"


void AValorantHUD::BeginPlay()
{
	Super::BeginPlay(); 

	bReplicates = true; 
	
	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;

	if (!PlayerWidget) 
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetOwningPlayerController(), PlayerWidgetClass, TEXT ("PlayerWidget"));
		PlayerWidget->AddToViewport(5); 
	}
	
}

AValorantHUD::AValorantHUD()
{

} 

void AValorantHUD::DrawHUD() 
{
	Super::DrawHUD();
	
}


void AValorantHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantHUD, ShopScreen);  
}

void AValorantHUD::ToggleStore()
{
	UWorld * world = GetWorld();
	if (!world) return;

	APlayerController * PlayerController = world->GetFirstPlayerController();
	if (!PlayerController) return;

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

