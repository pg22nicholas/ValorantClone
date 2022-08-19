// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent; 

UCLASS()
class VALORANTCLONE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent * ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent * ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HitDamage = 2.0f;
	
	UFUNCTION(Server, Reliable)
	void OnProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit); 

};
