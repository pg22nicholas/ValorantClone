// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Player/ValorantPlayerStateBase.h" 



void UPlayerWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

	CurrentHealthText->TextDelegate.BindDynamic(this, &UPlayerWidget::GetPlayerHealth);  
	
}

FText UPlayerWidget::GetPlayerHealth()
{
	if (AValorantPlayerBase * Player = GetOwningPlayerPawn<AValorantPlayerBase>())
	{
		return FText::AsNumber(Player->Health);  
	}

	return FText(); 

}
