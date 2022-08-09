// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"

#include "WeaponInterface.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AValorantPlayerBase::AValorantPlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	  

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("WEAPON"));
	Weapon->SetupAttachment(RootComponent); 
} 


void AValorantPlayerBase::Shoot()
{
	if (Weapon->GetClass() == nullptr) return;
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Cannon Shot");

	if (Weapon == nullptr) return;
	//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, LaserWeapon->GetChildActor()->GetName());
	
	if (Weapon->GetChildActorClass()->ImplementsInterface(UWeaponInterface::StaticClass()))
	{
		IWeaponInterface::Execute_Fire( Weapon->GetChildActor());    
	}
	
	
}

void AValorantPlayerBase::TakeDamage_Implementation(const float& InDamage)
{
	IDamagingInterface::TakeDamage_Implementation(InDamage);

	Health -= InDamage;

	if (Health <= 0)
	{
		Destroy(); 
	}
}

// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}




