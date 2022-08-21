// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"

#include "Interfaces/WeaponInterface.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/ValorantPlayerStateBase.h"
#include "Weapon/WeaponBase.h"

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
}



// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AValorantPlayerBase::SetDamage);
}

void AValorantPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerBase, Health);
}

void AValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AValorantPlayerBase::Shoot); 
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AValorantPlayerBase::Reload);  

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

void AValorantPlayerBase::Shoot_Implementation()
{
	if (Weapon->GetClass() == nullptr) return;
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Shot");

	if (Weapon == nullptr) return;
	//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, LaserWeapon->GetChildActor()->GetName());
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		weaponBase->Fire(); 
	}
}

void AValorantPlayerBase::Reload_Implementation() 
{
	if (Weapon->GetClass() == nullptr) return;
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Reload"); 

	if (Weapon == nullptr) return;
	//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, LaserWeapon->GetChildActor()->GetName());
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		weaponBase->Reload(); 
	}
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



