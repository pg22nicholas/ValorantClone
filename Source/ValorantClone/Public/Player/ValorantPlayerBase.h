// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagingInterface.h"
#include "GameFramework/Character.h"
#include "ValorantPlayerBase.generated.h"

class UChildActorComponent; 

UCLASS()
class VALORANTCLONE_API AValorantPlayerBase : public ACharacter, public IDamagingInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AValorantPlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UChildActorComponent* Weapon;

public:	

	void Shoot();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float Health = 100.0f;

	
	

	virtual void TakeDamage_Implementation(const float& InDamage) override;

};
