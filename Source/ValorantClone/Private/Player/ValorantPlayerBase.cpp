// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"

#include "Interfaces/WeaponInterface.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
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

	SkillManager = CreateDefaultSubobject<USkillManager>(TEXT("SkillManager"));
}



// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AValorantPlayerBase::SetDamage);
}

void AValorantPlayerBase::Stun_Implementation(float stunDuration)
{
	// TODO:
}

void AValorantPlayerBase::KnockBack_Implementation(FVector knockBackForce)
{
	// TODO:
}

void AValorantPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerBase, Health);
}

void AValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AValorantPlayerBase::Shoot);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AValorantPlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AValorantPlayerBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &AValorantPlayerBase::OnAbility1Pressed);
	PlayerInputComponent->BindAction("Ability1", IE_Released, this, &AValorantPlayerBase::OnAbility1Released);

	PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &AValorantPlayerBase::OnAbility2Pressed);
	PlayerInputComponent->BindAction("Ability2", IE_Released, this, &AValorantPlayerBase::OnAbility2Released);

	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AValorantPlayerBase::OnUltimatePressed);
	PlayerInputComponent->BindAction("Ultimate", IE_Released, this, &AValorantPlayerBase::OnUltimateReleased);
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
	
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Cannon Shot");

	if (Weapon == nullptr) return;
	//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, LaserWeapon->GetChildActor()->GetName());
	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		weaponBase->Fire(); 
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

void AValorantPlayerBase::OnAbility1Pressed()
{
	SkillManager->OnAbilityUsed(0);
}

void AValorantPlayerBase::OnAbility1Released()
{
	SkillManager->OnAbilityFinished(0);
}

void AValorantPlayerBase::OnAbility2Pressed()
{
	SkillManager->OnAbilityUsed(1);
}

void AValorantPlayerBase::OnAbility2Released()
{
	SkillManager->OnAbilityFinished(1);
}

void AValorantPlayerBase::OnUltimatePressed()
{
	SkillManager->OnAbilityUsed(2);
}

void AValorantPlayerBase::OnUltimateReleased()
{
	SkillManager->OnAbilityFinished(2);
}



