// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SkillManager.h"

#include "Ability/AbilityBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USkillManager::USkillManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USkillManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void USkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USkillManager::OnAbilityUsed(uint8 abilityIndex)
{
	if (Abilities.Num() < abilityIndex + 1) return;
	UWorld* world = GetWorld();
	if (!world) return;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;
	
	Abilities[abilityIndex]->StartAbility(PlayerController);
}

void USkillManager::OnAbilityFinished(uint8 abilityIndex)
{
	if (Abilities.Num() < abilityIndex + 1) return;
	Abilities[abilityIndex]->EndAbility();
}

void USkillManager::OnAbilityCancelled(uint8 abilityIndex)
{
	if (Abilities.Num() < abilityIndex + 1) return;
	Abilities[abilityIndex]->CancelAbility();
}

