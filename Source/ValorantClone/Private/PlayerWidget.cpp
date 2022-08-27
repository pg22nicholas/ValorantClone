// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Player/ValorantPlayerStateBase.h" 



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
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		return FText::AsNumber(Player->Health);  
	}

	return FText(); 

}

FText UPlayerWidget::GetPlayerMaxHealth()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		return FText::AsNumber(Player->Max_Health);  
	}

	return FText(); 
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
