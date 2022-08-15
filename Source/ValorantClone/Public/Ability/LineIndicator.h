// Copyright (C) Nicholas Johnson 2022
#pragma once

#include "CoreMinimal.h"
#include "Ability/GroundIndicator.h"
#include "LineIndicator.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ALineIndicator : public AGroundIndicator
{GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Width = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D LineDirection = FVector2D::ZeroVector;
	
};
