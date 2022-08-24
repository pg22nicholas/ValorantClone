// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityBase.generated.h"

// This class does not need to be modified.
UCLASS(Abstract)
class VALORANTCLONE_API AAbilityBase : public AActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	AAbilityBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Cooldown = 2.f;

	DECLARE_DELEGATE(FAbiltiyEndSignature)
	FAbiltiyEndSignature AbilityEnd;
 
	DECLARE_DELEGATE(FAbiltiyCancelSignature)
	FAbiltiyCancelSignature AbilityCancel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* AbilityData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 AbilityDataTableIndex = 0;

	// if the ability has a hold before it's performed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsHoldAbility = true;

	// Player controller of player that initiated this ability
	UPROPERTY()
	TWeakObjectPtr<APlayerController> CachedPlayerController;

	// Used for things like holding a charge before performing the ability
	virtual bool BeforeAbility(APlayerController* controller);
	// Performs the actual ability
	virtual bool PerformAbility();
	virtual bool CancelAbility() PURE_VIRTUAL(AAbilityBase::CancelAbility, return false; );

protected:
	bool bOnCooldown = false;
	FTimerHandle CooldownTimerHandle;

	void CooldownFinished();

	float TimeOnHoldStart = 0;

	FTimerHandle HoldTimerHandle;
	bool IsHolding = false;
};
