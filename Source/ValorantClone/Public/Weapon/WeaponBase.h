// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class USceneComponent;

UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANTCLONE_API AWeaponBase : public AActor  
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeaponBase();

	UFUNCTION(Server, Reliable)
	virtual void SER_Fire();
	virtual void SER_Fire_Implementation() PURE_VIRTUAL(AWeaponBase::SER_Fire(),);

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

	// UFUNCTION(Server, Reliable)
	// virtual void Reload();
	//
	// UFUNCTION(Server, Reliable) 
	// virtual void AddMagazine();
	
		
};
