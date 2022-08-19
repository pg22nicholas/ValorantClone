// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
AWeaponBase::AWeaponBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE COMPONENT")); 
	RootComponent = SceneComponent; 
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	WeaponMesh->SetupAttachment(SceneComponent); 
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DIRECTION ARROW"));
	Arrow->SetupAttachment(WeaponMesh);

	Barrel = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel"));
	Barrel->SetupAttachment(WeaponMesh);
	
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}





