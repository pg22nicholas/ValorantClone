// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ValorantHUD.generated.h"

/**
 * 
 */
class UShopScreen; 
class UPlayerWidget;

UCLASS()
class VALORANTCLONE_API AValorantHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	AValorantHUD();

	virtual void DrawHUD() override; 

	UFUNCTION()
	void ToggleStore();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) 
	TSubclassOf<UShopScreen> ShopScreenClass; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) 
	TSubclassOf<UPlayerWidget> PlayerWidgetClass; 
	
	UPROPERTY(BlueprintReadOnly)
	UShopScreen * ShopScreen = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UPlayerWidget* PlayerWidget = nullptr;
private:

	class UTexture2D* CrosshairTex; 


};
