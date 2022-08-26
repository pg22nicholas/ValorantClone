// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Cannon.h"

#include "Chaos/CollisionResolutionUtil.h"

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

	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetLocation(Barrel->GetComponentLocation());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = instigator;
//	const FVector Location = GetActorLocation();
//	SpawnTransform.SetLocation({Location.X, Location.Y, Location.Z + 70});   
	
	GetWorld()->SpawnActor<AActor>(Projectile,SpawnTransform, SpawnParams);
}


