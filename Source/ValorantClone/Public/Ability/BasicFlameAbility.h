// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "FlameArea.h"
#include "BasicFlameAbility.generated.h"


class AFlameArea;
/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ABasicFlameAbility : public AAbilityBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class  AFlameArea> FlameArea;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FlameDuration = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> LineCastType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> SphereTrace;
	
	virtual bool BeforeAbility(APlayerController* controller) override;
	virtual bool PerformAbility() override;
	virtual bool CancelAbility() override;
};
