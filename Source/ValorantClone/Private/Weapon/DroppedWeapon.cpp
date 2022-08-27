// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DroppedWeapon.h"

#include "Components/SphereComponent.h"
#include "Player/ValorantPlayerBase.h"
#include "Weapon/WeaponData.h"

ADroppedWeapon::ADroppedWeapon()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE")); 
	SphereCollision->SetupAttachment(WeaponMesh);

	bReplicates = true;

	
}

// When Weapon is picked Up 
void ADroppedWeapon::PickedUp()
{
	// maybe Sound
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "Picked  Up");  
	
	Destroy();  
}

void ADroppedWeapon::AllowPickUp_Implementation(UPrimitiveComponent* OverlappedComponent, 
                                 AActor* OtherActor, 
                                 UPrimitiveComponent* OtherComp, 
                                 int32 OtherBodyIndex, 
                                 bool bFromSweep, 
                                 const FHitResult &SweepResult) 
{
	if (AValorantPlayerBase * PlayerBase = Cast<AValorantPlayerBase>(OtherActor))
	{
		PlayerBase->PickUpWeapon = this;
		if (WeaponData)
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "Allow Pick Up " + WeaponData->WeaponName.ToString());
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "no data here " ); 
		}
	}
	
}

void ADroppedWeapon::DisAllowPickUp_Implementation(UPrimitiveComponent* OverlappedComp,
									AActor* OtherActor,
									UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex) 
{

	if (AValorantPlayerBase * PlayerBase = Cast<AValorantPlayerBase>(OtherActor))
	{
		PlayerBase->PickUpWeapon = nullptr; 
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Purple, "DisAllow Pick Up");
		//ADroppedWeapon::K2_DestroyActor(); 
	}

	
	
}

void ADroppedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADroppedWeapon::AllowPickUp);

	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ADroppedWeapon::DisAllowPickUp);
	
	//ADroppedWeapon::K2_DestroyActor();   
}
