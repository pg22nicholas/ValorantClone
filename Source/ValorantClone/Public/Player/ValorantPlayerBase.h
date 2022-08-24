// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "Ability/SkillManager.h"
#include "Interfaces/DamagingInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "ValorantPlayerBase.generated.h"

class UChildActorComponent; 

UCLASS()
class VALORANTCLONE_API AValorantPlayerBase : public ACharacter, public IDamagingInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* MeshArms; 

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* MeshBody;
	
	UPROPERTY(VisibleDefaultsOnly, Category=Weapon)
	UChildActorComponent* Weapon;

public:
	// Sets default values for this character's properties
	AValorantPlayerBase();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkillManager* SkillManager;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite) 
	float Health = 100.0f;

	UFUNCTION()
	void Stun_Implementation(float stunDuration) override;

	UFUNCTION()
	void KnockBack_Implementation(FVector knockBackForce) override;

protected:

	UFUNCTION(Server, Reliable)
	void SetDamagePoint(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
		UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION(Server, Reliable)
	void Shoot();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

private:
	UFUNCTION(Server, Reliable)
	void OnAbility1Pressed();
	UFUNCTION(Server, Reliable)
	void OnAbility1Released();

	UFUNCTION(Server, Reliable)
	void OnAbility2Pressed();
	UFUNCTION(Server, Reliable)
	void OnAbility2Released();

	UFUNCTION(Server, Reliable)
	void OnUltimatePressed();
	UFUNCTION(Server, Reliable)
	void OnUltimateReleased();

	bool IsStun = false;
	FTimerHandle StunTimerHandle;
	void EndStun();

	const float PlayerMass = 200;

};
