// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/WeaponInterface.h"
#include "Weapon/WeaponBase.h"
#include "Cannon.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ACannon : public AWeaponBase, public IWeaponInterface
{
	GENERATED_BODY()

protected:
	ACannon();
	virtual void BeginPlay() override;

	virtual void Fire() override;
};
