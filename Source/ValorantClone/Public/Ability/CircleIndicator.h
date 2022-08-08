// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/GroundIndicator.h"
#include "CircleIndicator.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ACircleIndicator : public AGroundIndicator
{
	GENERATED_BODY()

protected:
	virtual void PerformAttack() override;
	
};
