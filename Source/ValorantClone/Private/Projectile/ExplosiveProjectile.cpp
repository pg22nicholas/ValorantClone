// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ExplosiveProjectile.h"

#include "Interfaces/DamagingInterface.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExplosiveProjectile::AExplosiveProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = ProjectileMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->InitialSpeed = 4000.0f;  
	ProjectileMovement->ProjectileGravityScale = 0; 
}

// Called when the game starts or when spawned
void AExplosiveProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this,&AExplosiveProjectile::OnProjectileHit);
	
}

void AExplosiveProjectile::Explode()
{
	// TODO: Sound and VFX?
}

void AExplosiveProjectile::OnProjectileHit_Implementation(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UWorld* world = GetWorld();
	if (!world) return;

	APawn* instigator = GetInstigator();
	if (!instigator) return;

	AActor* owner = GetOwner();
	if (!owner) return;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(instigator);
	ignoreActors.Add(owner);
	
	if(OtherActor->GetClass()->ImplementsInterface(UDamagingInterface::StaticClass()))
	{
		UGameplayStatics::ApplyRadialDamage(world, HitDamage, Hit.Location,
			ExplosionRadius, UDamageType::StaticClass(), TArray<AActor*>(), owner, instigator->GetController());
	}
	Explode(); 
}





