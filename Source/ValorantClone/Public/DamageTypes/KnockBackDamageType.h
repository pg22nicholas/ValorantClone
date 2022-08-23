// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes/BaseDamageType.h"
#include "KnockBackDamageType.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API UKnockBackDamageType : public UBaseDamageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockBackForce = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockUpForce = 10.f; 

	virtual float ProcessDamage(AActor* Owner, AValorantPlayerBase* HitCharacter, FVector HitLocation) const override;
	
};
