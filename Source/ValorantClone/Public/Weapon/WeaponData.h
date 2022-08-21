// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * 
 */

class UStaticMeshComponent;

UCLASS(BlueprintType) 
class VALORANTCLONE_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")  
	bool PrimaryWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	int32 WeaponPrice = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category="Weapon Data")   
	FText WeaponName;
};
