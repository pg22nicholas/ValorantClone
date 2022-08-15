// Copyright (C) Nicholas Johnson 2022
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Radius = 0.5;
	
};
