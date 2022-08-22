// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerWidget.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class USceneComponent;
class UWeaponData;
class USphereComponent;

UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANTCLONE_API AWeaponBase : public AActor  
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeaponBase();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void StopFiring();
	
	UFUNCTION(BlueprintCallable) 
	void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Firing;
	
	UFUNCTION()
	void Equip();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent * Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Barrel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)   
	UPlayerWidget* PlayerWidget;
	
	UPROPERTY()
	FTimerHandle TimerHandle;
	
	// UFUNCTION(Server, Reliable)
	// virtual void Reload();
	//
	// UFUNCTION(Server, Reliable) 
	// virtual void AddMagazine();
	
		
};
