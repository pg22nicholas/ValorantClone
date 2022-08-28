// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class USceneComponent;
class UWeaponData;

UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANTCLONE_API AWeaponBase : public AActor  
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeaponBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent * Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Barrel;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* WeaponData;

	UFUNCTION()
	void Equip();

	UFUNCTION(Server, Reliable)
	void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Firing;

	UFUNCTION(Server, Reliable)
	void Fire();

	UFUNCTION(Server, Reliable)
	void StopFiring();
		
	UPROPERTY()
	FTimerHandle TimerHandle;

	// UFUNCTION(Server, Reliable)
	// virtual void Reload();
	//
	// UFUNCTION(Server, Reliable) 
	// virtual void AddMagazine();
	
		
};
