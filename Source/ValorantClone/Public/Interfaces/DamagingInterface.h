// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamagingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamagingInterface : public UInterface
{
	GENERATED_BODY()
};

class VALORANTCLONE_API IDamagingInterface
{
	GENERATED_BODY()

public:

	// TODO: Get team

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Damage Reaction")
	void Stun(float stunDuration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Damage Reaction")
	void KnockBack(FVector knockBackForce);

};
