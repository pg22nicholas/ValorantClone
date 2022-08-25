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
	float KnockBackForce = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockUpForce = 200.f; 

	virtual float ProcessDamage(AActor* Owner, APawn* HitCharacter, FVector HitLocation) const override;
	
};
