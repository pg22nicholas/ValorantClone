// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AK47.h"
#include "Weapon/WeaponData.h" 

AAK47::AAK47()
{
}

void AAK47::BeginPlay()
{
	Super::BeginPlay();
}

void AAK47::Fire()
{
	APawn* instigator = Cast<APawn>( GetParentActor());
	if (!instigator) return;


	
	if (WeaponData->CurrentProjectileNum <= 0) return;
	
	WeaponData->CurrentProjectileNum --;

	//PlayerWidget->CurrentProjectilesText->SetText(FText::AsNumber(WeaponData->CurrentProjectileNum));
	 
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "AK47 Shot");    

	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetLocation(Barrel->GetComponentLocation());

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = instigator;
	SpawnParams.Owner = this;
	//	const FVector Location = GetActorLocation();
	//	SpawnTransform.SetLocation({Location.X, Location.Y, Location.Z + 70});   
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, SpawnTransform.GetLocation().ToString()) ;    
	
	GetWorld()->SpawnActor<AActor>(WeaponData->Projectile,SpawnTransform, SpawnParams); 
}
