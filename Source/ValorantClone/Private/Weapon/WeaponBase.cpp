// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Weapon/WeaponData.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/HUD.h"
#include "player/ValorantPlayerStateBase.h"

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

void AWeaponBase::Fire()
{
	APawn* instigator = Cast<APawn>(GetParentActor());
	if (!instigator) return;
	if (!WeaponData) return;
	
	if (WeaponData->CurrentProjectileNum <= 0)
	{
		Reload();  
		return;
	}
	
	WeaponData->CurrentProjectileNum --;  
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Cannon Shot");    

	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetLocation(Barrel->GetComponentLocation());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = instigator;
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, SpawnTransform.GetLocation().ToString()) ;    
	
	GetWorld()->SpawnActor<AActor>(WeaponData->Projectile,SpawnTransform, SpawnParams);

	if (WeaponData->Automatic && Firing) 
	{
		GetWorldTimerManager().SetTimer( TimerHandle, this, &AWeaponBase::Fire, WeaponData->Rate, false);
	}
}

void AWeaponBase::StopFiring()
{
	if (!WeaponData) return; 
	if (WeaponData->Automatic) 
	{
		Firing = false;
	}
}

void AWeaponBase::Reload() 
{
	if (!WeaponData) return;

	if (WeaponData->AllAmmo < 0) return;

	if (WeaponData->AllAmmo < WeaponData->Magazine)
	{
		WeaponData->CurrentProjectileNum = WeaponData->AllAmmo;
		WeaponData->AllAmmo = 0;
	}
	else
	{
		WeaponData->CurrentProjectileNum = WeaponData->Magazine;
		WeaponData->AllAmmo -= WeaponData->Magazine;
	}
	
}


void AWeaponBase::Equip()
{

	if (WeaponData->WeaponMesh)
	{
		WeaponMesh = WeaponData->WeaponMesh;
	}
}

void AWeaponBase::BeginPlay() 
{
	Super::BeginPlay();

	if (!WeaponData) return; 
	//WeaponData->CurrentProjectileNum = WeaponData->Magazine;  
	
}
 




