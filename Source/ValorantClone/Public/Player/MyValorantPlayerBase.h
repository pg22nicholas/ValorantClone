// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ValorantPlayerBase.h"
#include "MyValorantPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AMyValorantPlayerBase : public AValorantPlayerBase
{
	GENERATED_BODY()

protected:
	virtual  void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
