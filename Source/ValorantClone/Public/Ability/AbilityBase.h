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

	DECLARE_DELEGATE(FAbiltiyEndSignature)
	FAbiltiyEndSignature AbilityEnd;
 
	DECLARE_DELEGATE(FAbiltiyCancelSignature)
	FAbiltiyCancelSignature AbilityCancel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* AbilityData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 AbilityDataTableIndex = 0;

	// Player controller of player that initiated this ability
	UPROPERTY()
	TWeakObjectPtr<APlayerController> CachedPlayerController;

	virtual void StartAbility(APlayerController* controller);
	virtual void EndAbility() PURE_VIRTUAL(AAbilityBase::EndAbility,);
	virtual bool CancelAbility() PURE_VIRTUAL(AAbilityBase::CancelAbility, return false; );

protected:
	bool bOnCooldown = false;
};
