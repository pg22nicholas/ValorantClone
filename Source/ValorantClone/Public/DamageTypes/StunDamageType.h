// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes/BaseDamageType.h"
#include "StunDamageType.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API UStunDamageType : public UBaseDamageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StunDuration;
	
	virtual float ProcessDamage(AActor* Owner, AValorantPlayerBase* HitCharacter, FVector HitLocation) override;
	
};
