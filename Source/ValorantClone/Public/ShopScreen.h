// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ShopScreen.generated.h"

/**
 * 
 */ 
class UListView;
class UButton;

UCLASS()
class VALORANTCLONE_API UShopScreen : public UUserWidget, public  IUserObjectListEntry

{
	GENERATED_BODY()

public: 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget)) 
	UListView* PrimaryWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UListView* SecondaryWeapons;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* BuyButton;
	
	virtual  void NativeOnInitialized() override;

	UFUNCTION()
	void Purchase();
};
