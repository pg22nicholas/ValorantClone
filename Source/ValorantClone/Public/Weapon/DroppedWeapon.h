// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "DroppedWeapon.generated.h"

class USphereComponent; 
/**
 * 
 */
UCLASS()
class VALORANTCLONE_API ADroppedWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:

	ADroppedWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollision;

    UFUNCTION (BlueprintCallable)
    void PickedUp();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void AllowPickUp(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult);
					  
	UFUNCTION(BlueprintCallable,Server, Reliable)
	void DisAllowPickUp(UPrimitiveComponent* OverlappedComp,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex); 


	UFUNCTION(Reliable, Server)
	void DestroyWeapon(); 
	
	virtual void BeginPlay() override;
};
