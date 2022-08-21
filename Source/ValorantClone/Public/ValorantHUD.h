// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ValorantHUD.generated.h"

/**
 * 
 */
class UShopScreen; 

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

	UPROPERTY(BlueprintReadOnly)
	UShopScreen * ShopScreen = nullptr;

private:

	class UTexture2D* CrosshairTex; 


};
