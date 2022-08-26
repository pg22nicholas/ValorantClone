// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveProjectile.generated.h"


class UProjectileMovementComponent;
class UStaticMeshComponent; 

UCLASS()
class VALORANTCLONE_API AExplosiveProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent * ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent * ProjectileMovement;

	UFUNCTION(BlueprintCallable)
	void Explode();

	UFUNCTION()
	void OnProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit); 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.0f, ClampMax = 100.0f))
	float HitDamage = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.0f, ClampMax = 100.0f))
	float MinExplosionDamage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.0f, ClampMax = 1000.0f)) 
	float ExplosionRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.0f, ClampMax = 100.0f))
	float ExplosionDamage = 5.0f; 



};
