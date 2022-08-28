// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"
#include "ValorantCloneGameState.h"
#include "Ability/SkillManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "DamageTypes/BaseDamageType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/ValorantPlayerStateBase.h"
#include "Weapon/WeaponBase.h"
#include "ValorantClone/ValorantCloneGameModeBase.h"
#include "Weapon/DroppedWeapon.h"
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

	SkillManager = CreateDefaultSubobject<USkillManager>(TEXT("SkillManager"));
}



void AValorantPlayerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
}

void AValorantPlayerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AValorantPlayerBase, CurrentWeapon);
	DOREPLIFETIME(AValorantPlayerBase, Money); 
}

// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	OnTakePointDamage.AddDynamic(this, &AValorantPlayerBase::SetDamagePoint);
	OnTakeRadialDamage.AddDynamic(this, &AValorantPlayerBase::SetDamageRadial);

	SetWeaponOnStart(); 
}

void AValorantPlayerBase::BuyWeapon_Implementation(UWeaponData* WeaponData)
{
	// Mo Money case:
	if (Money < WeaponData->WeaponPrice)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald, "Not Enough Money");
		return;
	}

	// Already owned:

	if (PrimaryWeapon == WeaponData || SecondaryWeapon == WeaponData)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald, "Weapon Exists");
		return;
	}


	// Money decrement
	Money -= WeaponData->WeaponPrice;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald, "Purchased");

	AddWeaponToArsenal(WeaponData);
}

void AValorantPlayerBase::DropWeapon_Implementation(UWeaponData* WeaponData)
{

	if (!DroppedWeapon) return; 
	
	// Spawn Parameters for dropped Weapon
	FTransform SpawnTransform = GetTransform();
	FActorSpawnParameters SpawnParams;


	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, "Dropped: " + WeaponData->WeaponName.ToString());

	// Spawn Dropped Weapon on the same place

	
	ADroppedWeapon* DropWeapon = GetWorld()->SpawnActor<ADroppedWeapon>(DroppedWeapon, SpawnTransform, SpawnParams);
	DropWeapon->WeaponData = WeaponData; 

	
}

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

void AValorantPlayerBase::Reload_Implementation()
{
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		weaponBase->Reload(); 
	}
}

void AValorantPlayerBase::SwitchWeapon_Implementation()
{
	// Swap Weapons (Secondary and Primary)
	if (!PrimaryWeapon || !SecondaryWeapon) return;

	if (PrimaryWeapon == CurrentWeapon)
	{
		CurrentWeapon = SecondaryWeapon;
	}
	else CurrentWeapon = PrimaryWeapon;

	if (!CurrentWeapon) return;

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, "Switch");
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, (CurrentWeapon->WeaponName).ToString());

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Black, FString::FromInt(Money) + " Money");
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Black, FString::FromInt(CurrentWeapon->CurrentProjectileNum) + " Bullets");

	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{
		// set WeaponData on current weapon to new WeaponData 
		weaponBase->WeaponData = CurrentWeapon;

		weaponBase->Equip();
	}
}

void AValorantPlayerBase::AddWeaponToArsenal_Implementation(UWeaponData* WeaponData)
{

	// Equip Purchased Weapon 
	AWeaponBase* WeaponBase = Cast<AWeaponBase>(Weapon->GetChildActor());

	if (!WeaponBase) return;


	WeaponBase->WeaponData = WeaponData;



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
	CurrentWeapon = WeaponData;

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

	//PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AValorantPlayerBase::Shoot);

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AValorantPlayerBase::Shoot);  
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AValorantPlayerBase::StopShooting); 
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AValorantPlayerBase::Reload);  
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AValorantPlayerBase::PickUp);
	
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AValorantPlayerBase::SwitchWeapon);  
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
		}

		if (ValorantPlayerState->GetCurrHealth() <= 0)
		{
			UWorld* world = GetWorld();
			if (!world) return;
			
			if (AValorantCloneGameModeBase* ValoGameMode = Cast<AValorantCloneGameModeBase>(UGameplayStatics::GetGameMode(world)))
			{
				ValoGameMode->PlayerDied(this);
			}
			Destroy(); 
		}
	}
}

AValorantCloneGameState* AValorantPlayerBase::GetValoGameState()
{
	UWorld* world = GetWorld();
	if (world)
	{
		return Cast<AValorantCloneGameState>(world->GetGameState());
	}
	return nullptr;
}

bool AValorantPlayerBase::IsStateCanMoveInput()
{
	if (AValorantCloneGameState* ValoGameState = GetValoGameState())
	{
		return ValoGameState->IsMatchValorantInProgress();
	}
	return false;
}

bool AValorantPlayerBase::IsStateCanAttack()
{
	if (AValorantCloneGameState* ValoGameState = GetValoGameState())
	{
		return ValoGameState->IsMatchValorantInProgress();
	}
	return false;
}

bool AValorantPlayerBase::IsStateCanBuy()
{
	if (AValorantCloneGameState* ValoGameState = GetValoGameState())
	{
		return ValoGameState->IsMatchValorantBuying();
	}
	return false;
}

void AValorantPlayerBase::Shoot_Implementation()
{
	if (!IsStateCanAttack()) return;
	if (Weapon->GetClass() == nullptr) return;
	
	if (Weapon == nullptr) return;
	
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


void AValorantPlayerBase::MoveForward(float Value)
{
	if (!IsStateCanMoveInput()) return;
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
	if (!IsStateCanMoveInput()) return;
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
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityUsed(0);
}

void AValorantPlayerBase::OnAbility1Released_Implementation()
{
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityFinished(0);
}

void AValorantPlayerBase::OnAbility2Pressed_Implementation()
{
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityUsed(1);
}

void AValorantPlayerBase::OnAbility2Released_Implementation()
{
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityFinished(1);
}

void AValorantPlayerBase::OnUltimatePressed_Implementation()
{
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityUsed(2);
}

void AValorantPlayerBase::OnUltimateReleased_Implementation()
{
	if (!IsStateCanAttack()) return;
	SkillManager->OnAbilityFinished(2);
}


TEAMS AValorantPlayerBase::GetTeam()
{
	AValorantPlayerStateBase* ValoPlayerState = Cast<AValorantPlayerStateBase>(GetPlayerState());
	if (ValoPlayerState)
	{
		return ValoPlayerState->Team;
	}
	return TEAMS::TEAM_A;
}






