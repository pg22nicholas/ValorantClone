// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BasicAOEDamageAbility.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

bool ABasicAOEDamageAbility::BeforeAbility(APlayerController* controller)
{
	if (!Super::BeforeAbility(controller)) return false;
	UWorld* world = GetWorld();
	if (!world) return false;
	
	return true;
}

bool ABasicAOEDamageAbility::PerformAbility()
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

	// get damage amount based on length held
	world->GetTimerManager().ClearTimer(HoldTimerHandle);
	float TimeHeld = GetGameTimeSinceCreation() - TimeOnHoldStart;
	float PercentOfMaxHeld = UKismetMathLibrary::Min(TimeHeld / HoldTime, 1);
	float damageToApply = UKismetMathLibrary::Max(MaxDamage * PercentOfMaxHeld, MinDamage);

	// Line trace to center point of AOE explosion
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(world, ViewportLocation, EndCast, LineCastType,
		false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		FVector HitLocation = HitResult.Location;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(CachedPlayerController->GetPawn());
		TArray<FHitResult> HitResults;
		// sphere trace to find all players inside sphere trace at a location
		UKismetSystemLibrary::SphereTraceMulti(world, HitLocation, HitLocation + FVector::UpVector * 10, Radius,
			SphereTrace, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResults, false);

		// Apply point damage to all actors hit
		for (FHitResult SphereHitResult : HitResults)
		{
			UGameplayStatics::ApplyPointDamage(SphereHitResult.GetActor(), damageToApply, HitLocation, SphereHitResult, CachedPlayerController.Get(), this, DamageType);
		}
	}
	return true;
}

bool ABasicAOEDamageAbility::CancelAbility()
{
	// TODO:
	return true;
}
