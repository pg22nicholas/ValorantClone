// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Player/ValorantPlayerStateBase.h"


void UPlayerWidget::ChangeMoneyText(int32 Money)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Blue, "Money update");     
	MoneyText->SetText(FText::AsNumber(Money));  
	
}


void UPlayerWidget::NativeOnInitialized() 
{
	Super::NativeOnInitialized();

 
	
	UWorld * World = GetWorld();
	if (!World) return;

	AValorantCloneGameModeBase* GameMode = World->GetAuthGameMode<AValorantCloneGameModeBase>();
	if (!GameMode) return;

	AValorantPlayerBase* Player = Cast<AValorantPlayerBase>(GameMode->DefaultPawnClass.GetDefaultObject()); 
	if (!Player) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	AValorantPlayerStateBase* PlayerSate = PlayerController->GetPlayerState<AValorantPlayerStateBase>();
	if (!PlayerSate) return;


	// Listen to Money Delegate to update HUD:
	PlayerSate->PurchaseDelegate.AddDynamic(this, &UPlayerWidget::ChangeMoneyText);  

}
