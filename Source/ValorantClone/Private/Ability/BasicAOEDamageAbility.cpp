// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BasicAOEDamageAbility.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ABasicAOEDamageAbility::StartAbility(APlayerController* controller)
{
	Super::StartAbility(controller);
	TimeOnHoldStart = GetGameTimeSinceCreation();
	UWorld* world = GetWorld();
	if (!world) return;

	IsHolding = true;
}

void ABasicAOEDamageAbility::EndAbility()
{
	if (!IsHolding) return;

	IsHolding = false;
	UWorld* world = GetWorld();
	if (!world) return;

	if (!CachedPlayerController.IsValid()) return;
	
	FVector ViewportLocation;
	FRotator ViewportRotation;
	CachedPlayerController->GetPlayerViewPoint(OUT ViewportLocation, OUT ViewportRotation);
	FVector EndCast = ViewportLocation + ViewportRotation.Vector() * 10000;

	world->GetTimerManager().ClearTimer(HoldTimerHandle);
	float TimeHeld = GetGameTimeSinceCreation() - TimeOnHoldStart;
	float PercentOfMaxHeld = UKismetMathLibrary::Min(TimeHeld / HoldTime, 1);
	float damageToApply = UKismetMathLibrary::Max(MaxDamage * PercentOfMaxHeld, MinDamage);
	
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(world, ViewportLocation, EndCast, LineCastType,
		false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		FVector HitLocation = HitResult.Location;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(CachedPlayerController->GetPawn());
		TArray<FHitResult> HitResults;
		UKismetSystemLibrary::SphereTraceMulti(world, HitLocation, HitLocation + FVector::UpVector * 10, Radius,
			SphereTrace, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResults, false);
		
		for (FHitResult SphereHitResult : HitResults)
		{
			UGameplayStatics::ApplyPointDamage(SphereHitResult.GetActor(), damageToApply, HitLocation, SphereHitResult, CachedPlayerController.Get(), this, DamageType);
		}
	}
}

bool ABasicAOEDamageAbility::CancelAbility()
{
	// TODO:
	return true;
}
