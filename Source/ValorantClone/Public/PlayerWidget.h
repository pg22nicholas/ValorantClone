// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerWidget.generated.h"


class UTextBlock;
class UProgressBar; 
/**
 * 
 */
UCLASS(Abstract)
class VALORANTCLONE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta=(BindWidget)) 
	UProgressBar * HealthBar;

	UPROPERTY(meta=(BindWidget)) 
	UTextBlock * CurrentHealthText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock * MaxHealthText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock * CurrentProjectilesText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock * MagazineText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock * AllProjectilesText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock * MoneyText;

protected:

	UFUNCTION()
	void ChangeHealthText(float Health) ; 
 
	virtual  void NativeOnInitialized() override;
};
