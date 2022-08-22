// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DroppedWeapon.h"

#include "Components/SphereComponent.h"
#include "Player/ValorantPlayerBase.h"

ADroppedWeapon::ADroppedWeapon()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE")); 
	SphereCollision->SetupAttachment(WeaponMesh); 
}

void ADroppedWeapon::AllowPickUp(UPrimitiveComponent* OverlappedComponent, 
                                 AActor* OtherActor, 
                                 UPrimitiveComponent* OtherComp, 
                                 int32 OtherBodyIndex, 
                                 bool bFromSweep, 
                                 const FHitResult &SweepResult)
{
	if (AValorantPlayerBase * PlayerBase = Cast<AValorantPlayerBase>(OtherActor))
	{
		PlayerBase->PickUpWeaponData = WeaponData;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "Allow Pick Up");  
	}
	
}

void ADroppedWeapon::DisAllowPickUp(UPrimitiveComponent* OverlappedComp,
									AActor* OtherActor,
									UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex) 
{

	if (AValorantPlayerBase * PlayerBase = Cast<AValorantPlayerBase>(OtherActor))
	{
		PlayerBase->PickUpWeaponData = nullptr;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "DisAllow Pick Up"); 
	}

	
	
}

void ADroppedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADroppedWeapon::AllowPickUp);

	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ADroppedWeapon::DisAllowPickUp); 
}
