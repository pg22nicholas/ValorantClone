// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AK47.h"

AAK47::AAK47()
{
}

void AAK47::BeginPlay()
{
	Super::BeginPlay();
}

void AAK47::Fire_Implementation()
{
	APawn* instigator = Cast<APawn>(GetOwner());
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "AK47 Shot");    

	const FTransform SpawnTransform = GetTransform();  
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = instigator;
	//	const FVector Location = GetActorLocation();
	//	SpawnTransform.SetLocation({Location.X, Location.Y, Location.Z + 70});   
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, SpawnTransform.GetLocation().ToString()) ;    
	
	GetWorld()->SpawnActor<AActor>(Projectile,SpawnTransform, SpawnParams); 
}
