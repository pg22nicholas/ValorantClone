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
{
	GENERATED_BODY()

protected:

	float Width = 1;
	float Length = 100;
	
};
