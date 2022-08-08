// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UWeaponBase::UWeaponBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DIRECTION ARROW"));
	Arrow->SetupAttachment(WeaponMesh);
	// ...
}


// Called when the game starts
void UWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


