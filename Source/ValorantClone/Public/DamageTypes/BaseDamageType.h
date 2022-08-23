// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "Player/ValorantPlayerBase.h"
#include "BaseDamageType.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API UBaseDamageType : public UDamageType
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=( ClampMin=0 ))
	float DamageMultiplier = 1;

	/**
	 * Process the damage and return the damage multiplier from the hit
	 * @param Owner			Character that caused this attack
	 * @param HitCharacter	Player Character that was hit
	 * @param HitLocation	Location the player was hit
	 */
	UFUNCTION()
	virtual float ProcessDamage(AActor* Owner, AValorantPlayerBase* HitCharacter, FVector HitLocation) const;
};
