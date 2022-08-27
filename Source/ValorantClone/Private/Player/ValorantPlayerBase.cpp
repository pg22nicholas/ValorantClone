// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerWidget.h" 
#include "Weapon/WeaponBase.h"
#include "Weapon/WeaponData.h"

// Sets default values
AValorantPlayerBase::AValorantPlayerBase()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, 64.f)); 
	CameraComponent->bUsePawnControlRotation = true;

	MeshArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshArms"));
	MeshArms->SetOnlyOwnerSee(true);				
	MeshArms->SetupAttachment(CameraComponent);	
	MeshArms->bCastDynamicShadow = false;			
	MeshArms->CastShadow = false;
	  
	MeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshBody"));
	MeshBody->SetOwnerNoSee(true);			
	MeshBody->bCastDynamicShadow = true;			
	MeshBody->CastShadow = true;
	MeshBody->SetupAttachment(MeshArms);
	
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(MeshArms);

	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		if (weaponBase->WeaponData)
		{
			CurrentWeapon = weaponBase->WeaponData; 
		}
	}
}



// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AValorantPlayerBase::SetDamage);

	
	// Setup Primary Secondary and Current Weapon
	SetWeaponOnStart(); 
} 


void AValorantPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerBase, Health); 
	DOREPLIFETIME(AValorantPlayerBase, CurrentWeapon);
	
}

void AValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AValorantPlayerBase::Shoot); 
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AValorantPlayerBase::StopShooting); 
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AValorantPlayerBase::Reload);  
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AValorantPlayerBase::PickUp);
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &AValorantPlayerBase::Test);
	
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AValorantPlayerBase::SwitchWeapon);  
 
	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AValorantPlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AValorantPlayerBase::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	
}


void AValorantPlayerBase::SetDamage_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	
	if (Health <= 0)
	{ 
		Destroy(); 
	}
}

void AValorantPlayerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}



// WEAPON USE FUNCTIONS

void AValorantPlayerBase::Shoot_Implementation() 
{
	
	if (Weapon == nullptr) return;  
	
	if (Weapon->GetClass() == nullptr) return; 
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		weaponBase->Firing = true; 
		weaponBase->Fire(); 
	}
}

void AValorantPlayerBase::StopShooting_Implementation() 
{
	
	if (Weapon == nullptr) return;  
	
	if (Weapon->GetClass() == nullptr) return; 
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		weaponBase->StopFiring();  
	}
}

void AValorantPlayerBase::Reload_Implementation()   
{
 
	if (Weapon == nullptr) return;
	
	if (Weapon->GetClass() == nullptr) return; 
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		weaponBase->Reload(); 
	}
}


// WEAPON CHANGE FUNCTIONS


void AValorantPlayerBase::PickUp_Implementation()
{
	if (!PickUpWeapon) return;
	if (!PickUpWeapon->WeaponData) return;


	// stop if current is the same
    if (PickUpWeapon->WeaponData == PrimaryWeapon || PickUpWeapon->WeaponData == SecondaryWeapon) return;

	// Add it 
	AddWeaponToArsenal(PickUpWeapon->WeaponData);
	
	PickUpWeapon->PickedUp();     
}

// Swap Weapons
void AValorantPlayerBase::SwitchWeapon_Implementation()  
{

	// Swap Weapons (Secondary and Primary)
	if (!PrimaryWeapon ||  !SecondaryWeapon) return; 
	
	if (PrimaryWeapon == CurrentWeapon)
	{
		CurrentWeapon = SecondaryWeapon;
	}
	else CurrentWeapon = PrimaryWeapon;


	if (!CurrentWeapon) return; 
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, "Switch"); 
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, (CurrentWeapon->WeaponName).ToString()); 

	Money --;
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Black, FString::FromInt(Money) + " Money");
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Black, FString::FromInt(CurrentWeapon->CurrentProjectileNum)+ " Bullets"); 
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Black, FString::FromInt(Health)+ " HP");   
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		// set WeaponData on current weapon to new WeaponData 
		weaponBase->WeaponData = CurrentWeapon;
		
		weaponBase->Equip(); 
	}
}

// Drop Current Weapon
void AValorantPlayerBase::DropWeapon_Implementation(UWeaponData* WeaponData)
{
	
	// Spawn Parameters for dropped Weapon
	FTransform SpawnTransform = GetTransform();
	FActorSpawnParameters SpawnParams;
	

	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Dropped: " + WeaponData->WeaponName.ToString()) ;       

	// Spawn Dropped Weapon on the same place
	GetWorld()->SpawnActor<ADroppedWeapon>(DroppedWeapon, SpawnTransform, SpawnParams)->WeaponData = WeaponData; 
	
}


void AValorantPlayerBase::AddWeaponToArsenal_Implementation(UWeaponData* WeaponData)  
{
	// Equip Purchased Weapon 
	AWeaponBase* WeaponBase = Cast<AWeaponBase>(Weapon->GetChildActor());

	if (!WeaponBase) return;  

	
	WeaponBase->WeaponData = WeaponData;
	CurrentWeapon = WeaponData;
	
		
	// Drop Previous Weapon
	// Add Weapon to collection
	if (WeaponData->PrimaryWeapon) 
	{
		if (PrimaryWeapon)
		{
			DropWeapon(PrimaryWeapon);
			//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Dropped: " + PrimaryWeapon->WeaponName.ToString()) ;     
		}
		PrimaryWeapon = WeaponData;
	}
	else
	{
		if (SecondaryWeapon)
			DropWeapon(SecondaryWeapon); 
		SecondaryWeapon = WeaponData;
	}
}

void AValorantPlayerBase::SetWeaponOnStart_Implementation() 
{
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		if (!weaponBase->WeaponData) return; 

		// Check what is the initial WeaponData on Owning Weapon (Set In Blueprint)
		if (weaponBase->WeaponData->PrimaryWeapon)
		{
			PrimaryWeapon = weaponBase->WeaponData;
			CurrentWeapon = PrimaryWeapon;
		}
		else
		{
			SecondaryWeapon = weaponBase->WeaponData;
			CurrentWeapon = SecondaryWeapon;  
		}
		
	}
}

void AValorantPlayerBase::BuyWeapon_Implementation(UWeaponData* WeaponData)
{
	// Mo Money case:
	if (Money < WeaponData->WeaponPrice)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Not Enough Money");
		return;  
	}

	// Already owned:
	
	if (PrimaryWeapon == WeaponData || SecondaryWeapon == WeaponData)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Weapon Exists"); 
		return;
	}
    
	
	// Money decrement
	Money-=WeaponData->WeaponPrice;
	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald , "Purchased"); 
	
	AddWeaponToArsenal(WeaponData);  
}



// MOVING FUNCTIONS


void AValorantPlayerBase::Test_Implementation()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, "Test");

	Health --;
	Money --; 
}

void AValorantPlayerBase::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AValorantPlayerBase::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}



