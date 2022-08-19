// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ValorantHUD.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AValorantHUD : public AHUD
{
	GENERATED_BODY()

public:

	AValorantHUD();

	virtual void DrawHUD() override;

private:

	class UTexture2D* CrosshairTex; 
	
};
