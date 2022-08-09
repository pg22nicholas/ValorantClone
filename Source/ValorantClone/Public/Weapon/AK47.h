// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "Weapon/WeaponBase.h"
#include "AK47.generated.h"

/**
 * 
 */
UCLASS()
class VALORANTCLONE_API AAK47 : public AWeaponBase, public IWeaponInterface
{
	GENERATED_BODY()

protected:
	AAK47(); 
	virtual void BeginPlay() override;

	virtual void Fire_Implementation() override;
};

