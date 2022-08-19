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

void ACannon::Fire_Implementation()
{
	APawn* instigator = Cast<APawn>(GetOwner());
	if (!instigator) return;
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Cannon Shot");    

	const FTransform SpawnTransform = GetTransform();  
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = instigator;
//	const FVector Location = GetActorLocation();
//	SpawnTransform.SetLocation({Location.X, Location.Y, Location.Z + 70});   
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, SpawnTransform.GetLocation().ToString()) ;    
	
	GetWorld()->SpawnActor<AActor>(Projectile,SpawnTransform, SpawnParams);
}


