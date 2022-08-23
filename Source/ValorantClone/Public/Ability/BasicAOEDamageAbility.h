// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "BasicAOEDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ABasicAOEDamageAbility : public AAbilityBase
{
	GENERATED_BODY()

public:
	virtual void StartAbility(APlayerController* controller) override;
	virtual void EndAbility() override;
	virtual bool CancelAbility() override;
	
};
