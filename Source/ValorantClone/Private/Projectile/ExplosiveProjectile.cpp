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
	TArray<FHitResult> HitResults;

	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();

	const FCollisionShape ColShape = FCollisionShape::MakeSphere(ExplosionRadius);

	const bool Hit = GetWorld()->SweepMultiByChannel(HitResults, 
		Start,
		End, FQuat::Identity, ECC_Visibility, ColShape); 
 
	DrawDebugSphere(GetWorld(), Start, ExplosionRadius, 50, FColor::Orange, false, 2.0f); 

	if (Hit)
	{
		for (auto const HitResult : HitResults)  
		{ 
			//	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Orange,*HitResult.Actor->GetName());
			
			if (HitResult.Actor->GetClass()->ImplementsInterface(UDamagingInterface::StaticClass())) 
			{
				HitResult.GetActor()->TakeDamage(ExplosionDamage, FDamageEvent(), GetInstigator()->GetController(), GetInstigator());
			}
		}
		Destroy();  
	}
}

void AExplosiveProjectile::OnProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UWorld* world = GetWorld();
	if (!world) return;

	APawn* instigator = Cast<APawn>(GetInstigator());
	if (!instigator) return;
	
	if(OtherActor->GetClass()->ImplementsInterface(UDamagingInterface::StaticClass()))
	{
		UGameplayStatics::ApplyRadialDamage(world, HitDamage, Hit.Location,
			ExplosionRadius, UDamageType::StaticClass(), TArray<AActor*>(), instigator, instigator->GetController());
	}
	Explode(); 
}





