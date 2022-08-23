// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManager.generated.h"


class AAbilityBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALORANTCLONE_API USkillManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AAbilityBase>> AbilityTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 MaxNumberAbilities = 3;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnAbilityUsed(uint8 abilityIndex);
	void OnAbilityFinished(uint8 abilityIndex);
	void OnAbilityCancelled(uint8 abilityIndex);

private:
	TArray<AAbilityBase*> Abilities;

	UFUNCTION(Server, Reliable)
	void InitiateAbilities();

	void InitiateAbilityHelper(uint8 index);
		
};
