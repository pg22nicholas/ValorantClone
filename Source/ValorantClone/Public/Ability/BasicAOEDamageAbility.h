// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "DamageTypes/KnockBackDamageType.h"
#include "DamageTypes/StunDamageType.h"
#include "BasicAOEDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ABasicAOEDamageAbility : public AAbilityBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HoldTime = 3.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxDamage = 50.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinDamage = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Radius = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseDamageType> DamageType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> LineCastType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> SphereTrace;
	
	virtual bool BeforeAbility(APlayerController* controller) override;
	virtual bool PerformAbility() override;
	virtual bool CancelAbility() override;

	
};