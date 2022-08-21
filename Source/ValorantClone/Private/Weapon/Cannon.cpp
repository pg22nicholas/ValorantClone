// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Cannon.h"

#include "Chaos/CollisionResolutionUtil.h"
#include "Weapon/WeaponData.h"

ACannon::ACannon()
{
	
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACannon::Fire()
{
	APawn* instigator = Cast<APawn>(GetParentActor());
	if (!instigator) return;


	if (WeaponData->CurrentProjectileNum <= 0) return; 
	
	WeaponData->CurrentProjectileNum --;
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Cannon Shot");    

	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetLocation(Barrel->GetComponentLocation());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = instigator;
//	const FVector Location = GetActorLocation();
//	SpawnTransform.SetLocation({Location.X, Location.Y, Location.Z + 70});   
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, SpawnTransform.GetLocation().ToString()) ;    
	
	GetWorld()->SpawnActor<AActor>(WeaponData->Projectile,SpawnTransform, SpawnParams); 
}


