// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "player/ValorantPlayerControllerBase.h"
#include "Player/ValorantPlayerStateBase.h" 
#include "Weapon/WeaponData.h"


void UPlayerWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

	CurrentHealthText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetPlayerHealth);
	MaxHealthText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetPlayerMaxHealth);
	MoneyText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetPlayerMoney);
	CurrentProjectilesText->TextDelegate.BindDynamic(this, &UPlayerWidget::UPlayerWidget::GetWeaponCurrentAmmo);
	MagazineText->TextDelegate.BindDynamic(this, &UPlayerWidget::UPlayerWidget::GetWeaponMagazine);
	AllProjectilesText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetWeaponAllAmmo);
	WeaponNameText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetWeaponName);
}



FText UPlayerWidget::GetPlayerHealth()
{
	AValorantPlayerControllerBase* ValorantController = GetWorld()->GetFirstPlayerController<AValorantPlayerControllerBase>();
	if (!ValorantController) return FText(); 

	AValorantPlayerStateBase* ValorantState = ValorantController->GetPlayerState<AValorantPlayerStateBase>();
	if (!ValorantState) return FText();

	return FText::AsNumber(ValorantState->GetMaxHealth()); 

}

FText UPlayerWidget::GetPlayerMaxHealth()
{
	AValorantPlayerControllerBase* ValorantController = GetWorld()->GetFirstPlayerController<AValorantPlayerControllerBase>();
	if (!ValorantController) return FText(); 

	AValorantPlayerStateBase* ValorantState = ValorantController->GetPlayerState<AValorantPlayerStateBase>();
	if (!ValorantState) return FText();

	return FText::AsNumber(ValorantState->GetCurrHealth());
}

FText UPlayerWidget::GetPlayerMoney()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		return FText::AsNumber(Player->Money);
	}

	return FText(); 
}

FText UPlayerWidget::GetWeaponCurrentAmmo()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		if (Player->CurrentWeapon){
			return FText::AsNumber(Player->CurrentWeapon->CurrentProjectileNum); 
		}
		return FText();  
	}
	
	return FText(); 
}

FText UPlayerWidget::GetWeaponMagazine()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		if (Player->CurrentWeapon){
			return FText::AsNumber(Player->CurrentWeapon->Magazine); 
		}
		return FText();  
	}

	return FText(); 
}

FText UPlayerWidget::GetWeaponAllAmmo()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		if (Player->CurrentWeapon){
			return FText::AsNumber(Player->CurrentWeapon->AllAmmo);  
		}
		return FText();  
	}

	return FText(); 
}

FText UPlayerWidget::GetWeaponName()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		if (Player->CurrentWeapon){
			return Player->CurrentWeapon->WeaponName;   
		}
		return FText();  
	}

	return FText(); 
}
