// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityStruct.generated.h"

USTRUCT(BlueprintType)
struct FAbilityStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 SkillID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsBlockingAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsBlockingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsBlockingDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsBlockingDamageFeedback;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsStun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHoldTime;
};
