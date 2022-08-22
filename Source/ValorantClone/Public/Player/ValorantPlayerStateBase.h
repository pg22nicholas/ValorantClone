// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "ValorantPlayerStateBase.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPurchaseEvent, int32, Money);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponSwitchEvent, FText, CurAmmoName);
/**
 * 
 */
class UWeaponData; 

UCLASS(BlueprintType) 
class VALORANTCLONE_API AValorantPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:

	AValorantPlayerStateBase();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Max_Health = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)  
	float CurHealth = 100; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	int32 Money = 100;

	UFUNCTION(Server, Reliable) 
	void BuyWeapon(UWeaponData* Weapon);  
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TArray<UWeaponData*> OwnedWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)  
	UWeaponData* CurrentWeapon;
	
	void SetPlayerType(PLAYABLE_CHARACTERS playerType) { PlayerType = playerType; }
	PLAYABLE_CHARACTERS GetPlayerType() { return PlayerType; }

	UPROPERTY()
	FPurchaseEvent PurchaseDelegate;

	UPROPERTY()
	FWeaponSwitchEvent WeaponSwitchDelegate;

	UFUNCTION(Server, Reliable,BlueprintCallable)
	void SwitchWeapon();
	
private:
	
	// Type of player class this player state represents
	PLAYABLE_CHARACTERS PlayerType;

	virtual void BeginPlay() override;
	
};
