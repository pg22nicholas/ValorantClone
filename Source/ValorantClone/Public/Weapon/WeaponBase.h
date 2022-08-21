// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	virtual void Fire() PURE_VIRTUAL(AWeaponBase::FireLogic, );

	UFUNCTION(BlueprintCallable, Server, Reliable) 
	void Reload ();
	 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent * Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Barrel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* WeaponData;
	
	
	
	// UFUNCTION(Server, Reliable)
	// virtual void Reload();
	//
	// UFUNCTION(Server, Reliable) 
	// virtual void AddMagazine();
	
		
};
