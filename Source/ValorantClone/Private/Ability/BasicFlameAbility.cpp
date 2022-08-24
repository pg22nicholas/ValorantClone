// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BasicFlameAbility.h"

#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

bool ABasicFlameAbility::BeforeAbility(APlayerController* controller)
{
	if (!Super::BeforeAbility(controller)) return false;
	UWorld* world = GetWorld();
	if (!world) return false;
	
	return true;
}

bool ABasicFlameAbility::PerformAbility()
{
	if (!Super::PerformAbility()) return false;
	
	UWorld* world = GetWorld();
	if (!world) return false;

	if (!CachedPlayerController.IsValid()) return false;

	// get player camera's rotation and position to line trace
	FVector ViewportLocation;
	FRotator ViewportRotation;
	CachedPlayerController->GetPlayerViewPoint(OUT ViewportLocation, OUT ViewportRotation);
	FVector EndCast = ViewportLocation + ViewportRotation.Vector() * 10000;


	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(world, ViewportLocation, EndCast, LineCastType,
		false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		FVector HitLocation = HitResult.Location;
		
		// spawning the Flame Area actor
		AActor* NewFlame = GetWorld()->SpawnActor<AFlameArea>(FlameArea, HitLocation, GetActorRotation());
		NewFlame->SetLifeSpan(FlameDuration);
	}
	
	return true;
}

bool ABasicFlameAbility::CancelAbility()
{
	return  true;
	
}
