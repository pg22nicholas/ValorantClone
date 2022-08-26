// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"

#include "Ability/SkillManager.h"
#include "Interfaces/WeaponInterface.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DamageTypes/BaseDamageType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/ValorantPlayerStateBase.h"
#include "Weapon/WeaponBase.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"

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


void AValorantPlayerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakePointDamage.AddDynamic(this, &AValorantPlayerBase::SetDamagePoint);
	OnTakeRadialDamage.AddDynamic(this, &AValorantPlayerBase::SetDamageRadial);
}

void AValorantPlayerBase::Stun_Implementation(float stunDuration)
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && ValorantPlayerState->GetIsStun()) return;
	
	ValorantPlayerState->SetIsStun(true);
	UWorld* world = GetWorld();
	world->GetTimerManager().SetTimer(StunTimerHandle, this, &AValorantPlayerBase::EndStun, stunDuration, false);
}

void AValorantPlayerBase::EndStun()
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState) ValorantPlayerState->SetIsStun(false);
}

void AValorantPlayerBase::KnockBack_Implementation(FVector knockBackForce)
{
	GetCharacterMovement()->AddImpulse(knockBackForce * PlayerMass);
}

void AValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AValorantPlayerBase::Shoot);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AValorantPlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AValorantPlayerBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AValorantPlayerBase::YawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AValorantPlayerBase::PitchInput);
	
	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &AValorantPlayerBase::OnAbility1Pressed);
	PlayerInputComponent->BindAction("Ability1", IE_Released, this, &AValorantPlayerBase::OnAbility1Released);

	PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &AValorantPlayerBase::OnAbility2Pressed);
	PlayerInputComponent->BindAction("Ability2", IE_Released, this, &AValorantPlayerBase::OnAbility2Released);

	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AValorantPlayerBase::OnUltimatePressed);
	PlayerInputComponent->BindAction("Ultimate", IE_Released, this, &AValorantPlayerBase::OnUltimateReleased);
}

void AValorantPlayerBase::SetDamagePoint(AActor* DamagedActor, float Damage,
	AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
	FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	SetDamage(Damage, HitLocation, DamageType, DamageCauser);
}

void AValorantPlayerBase::SetDamageRadial(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	SetDamage(Damage, HitInfo.Location, DamageType, DamageCauser);
}

void AValorantPlayerBase::SetDamage(float Damage, FVector HitLocation, const UDamageType* DamageType, AActor* DamageCauser)
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && GetLocalRole() == ROLE_Authority)
	{
		const UBaseDamageType* BaseDamageType = Cast<UBaseDamageType>(DamageType);
		if (BaseDamageType)
		{
			float DamageMultiplier = BaseDamageType->ProcessDamage(DamageCauser, this, HitLocation);
			ValorantPlayerState->SetCurrHealth(ValorantPlayerState->GetCurrHealth() - (Damage * DamageMultiplier));
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, FString::SanitizeFloat(ValorantPlayerState->GetCurrHealth()));
		}

		if (ValorantPlayerState->GetCurrHealth() <= 0)
		{
			Destroy(); 
		}
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
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && ValorantPlayerState->GetIsStun()) return;
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AValorantPlayerBase::MoveRight(float Value)
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && ValorantPlayerState->GetIsStun()) return;
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AValorantPlayerBase::YawInput(float Val)
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && ValorantPlayerState->GetIsStun()) return;
	if (Val != 0.0f)
	{
		AddControllerYawInput(Val);
	}
}

void AValorantPlayerBase::PitchInput(float Val)
{
	ValorantPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValorantPlayerState && ValorantPlayerState->GetIsStun()) return;
	if (Val != 0.0f)
	{
		AddControllerPitchInput(Val);
	}
}

void AValorantPlayerBase::OnAbility1Pressed_Implementation()
{
	SkillManager->OnAbilityUsed(0);
}

void AValorantPlayerBase::OnAbility1Released_Implementation()
{
	SkillManager->OnAbilityFinished(0);
}

void AValorantPlayerBase::OnAbility2Pressed_Implementation()
{
	SkillManager->OnAbilityUsed(1);
}

void AValorantPlayerBase::OnAbility2Released_Implementation()
{
	SkillManager->OnAbilityFinished(1);
}

void AValorantPlayerBase::OnUltimatePressed_Implementation()
{
	SkillManager->OnAbilityUsed(2);
}

void AValorantPlayerBase::OnUltimateReleased_Implementation()
{
	SkillManager->OnAbilityFinished(2);
}


TEAMS AValorantPlayerBase::GetTeam()
{
	return Team;
}

void AValorantPlayerBase::SetTeam(TEAMS team)
{
	Team = team;
}

void AValorantPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerBase, Team);
}





