// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "Player/ValorantPlayerStateBase.h"

void UPlayerWidget::ChangeHealthText(float Health) 
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Blue, FString::FromInt(Health  + 100));    
	MaxHealthText->Text = FText::AsNumber(Health);   
}

void UPlayerWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

	UWorld * World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	AValorantPlayerBase* Player = PlayerController->GetPawn<AValorantPlayerBase>();
	if (!Player) return;
 
	Player->PlayerHit.AddDynamic(this, &UPlayerWidget::ChangeHealthText);

		
	//MaxHealthText->Text = FText::AsNumber(PlayerState->Max_Health);  

	//MagazineText->Text = FText::AsNumber(PlayerState->CurrentWeapon->Magazine);  
}
