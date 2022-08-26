// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/FlameArea.h"

#include "Interfaces/DamagingInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlameArea::AFlameArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	SetRootComponent(BodyMesh);
	
	BodyMesh->SetSimulatePhysics(true);
	BodyMesh->SetNotifyRigidBodyCollision(true);
	BodyMesh->SetConstraintMode(EDOFMode::XYPlane);

	bReplicates = true;

}

// Called when the game starts or when spawned
void AFlameArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlameArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Counter += DeltaTime;
}

void AFlameArea::OnFlameHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* instigator = Cast<APawn>(GetInstigator());
	if (!instigator) return;

	AActor* owner = GetOwner();
	if (!owner) return;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(instigator);
	//ignoreActors.Add(owner);
	
	if(OtherActor->GetClass()->ImplementsInterface(UDamagingInterface::StaticClass()) && Counter >= DamageCooldown)
	{
		UGameplayStatics::ApplyDamage(OtherActor, FlameDamage, instigator->GetController(), owner, UDamageType::StaticClass());
		Counter = 0;
	}
}

