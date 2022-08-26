// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "DamageTypes/KnockBackDamageType.h"
#include "DamageTypes/StunDamageType.h"
#include "BasicWallCreationAbility.generated.h"

class AStaticMeshActor;
class UStaticMesh;
/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ABasicWallCreationAbility : public AAbilityBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> WallObject;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ObjectScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WallDuration = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> LineCastType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> SphereTrace;
	
	virtual bool BeforeAbility(APlayerController* controller) override;
	virtual bool PerformAbility() override;
	virtual bool CancelAbility() override;
};
