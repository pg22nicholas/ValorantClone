// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerWidget.h"
#include "ValorantHUD.h"
#include "player/ValorantPlayerStateBase.h"
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
	
	UWorld * World = GetWorld();
	if (!World) return;
	
	APlayerController * PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	AValorantHUD* HUD = PlayerController->GetHUD<AValorantHUD>();
	if (!HUD) return;

	UPlayerWidget* Widget = HUD->PlayerWidget;
	if (!Widget) return;

	PlayerWidget = Widget;

	PlayerWidget->MaxHealthText->SetText(FText::AsNumber(Max_Health)); 
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
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AValorantPlayerBase::StopShooting); 
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AValorantPlayerBase::Reload);  
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AValorantPlayerBase::PickUp);
	
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

	if (PlayerWidget)
	{
		PlayerWidget->CurrentHealthText->SetText(FText::AsNumber(Health));
	} 
	
	if (Health <= 0)
	{ 
		Destroy(); 
	}
}

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

void AValorantPlayerBase::PickUp_Implementation()
{
	if (!PickUpWeaponData) return;

	if (AValorantPlayerStateBase* ValorantState =  GetPlayerState<AValorantPlayerStateBase>())
	{
		ValorantState->GetNewWeapon(PickUpWeaponData);
	}
}

void AValorantPlayerBase::SwitchWeapon_Implementation()  
{
	AValorantPlayerStateBase* ValorantState = GetPlayerState<AValorantPlayerStateBase>();
	if (!ValorantState) return;

	ValorantState->SwitchWeapon();

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, "Switch"); 
	
	if (!ValorantState->CurrentWeapon) return;  

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Magenta, (ValorantState->CurrentWeapon->WeaponName).ToString()); 

	
	if (AWeaponBase* weaponBase = Cast<AWeaponBase>(Weapon->GetChildActor())) 
	{
		weaponBase->WeaponData = ValorantState->CurrentWeapon;

		weaponBase->Equip(); 
	}
}

void AValorantPlayerBase::DropWeapon_Implementation(UWeaponData* WeaponData)
{
	AValorantPlayerStateBase* ValorantState = GetPlayerState<AValorantPlayerStateBase>();
	if (!ValorantState) return;

	if (AWeaponBase* WeaponBase = Cast<AWeaponBase>(Weapon->GetChildActor()))
	{

		FTransform SpawnTransform = GetTransform();
		FActorSpawnParameters SpawnParams;
		
	
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black, "Spawned Old Weapon") ;    
		
		GetWorld()->SpawnActor<ADroppedWeapon>(DroppedWeapon, SpawnTransform, SpawnParams)->WeaponData = WeaponData; 

		
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



