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
	float damageToApply = MaxDamage * PercentOfMaxHeld;
	
	FHitResult HitResult;
	if (UKismetSystemLibrary::LineTraceSingleForObjects(world, ViewportLocation, EndCast, LineCastType,
		false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		FVector HitLocation = HitResult.Location;
		UKismetSystemLibrary::DrawDebugSphere(world, HitLocation, Radius, 12, FLinearColor::Blue, 5);
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(CachedPlayerController->GetPawn());
		TArray<AActor*> HitActors;
		UKismetSystemLibrary::SphereOverlapActors(world, HitLocation, Radius, SphereCastType, nullptr, ActorsToIgnore, HitActors);
		for (AActor* HitActor : HitActors)
		{
			UGameplayStatics::ApplyDamage(HitActor, damageToApply, CachedPlayerController.Get(), this, UDamageType::StaticClass());
			UGameplayStatics::ApplyDamage(HitActor, 0, CachedPlayerController.Get(), this, StunDamageType);
			UGameplayStatics::ApplyDamage(HitActor, 0, CachedPlayerController.Get(), this, KnockBackDamageType);
		}
	}
}

bool ABasicAOEDamageAbility::CancelAbility()
{
	// TODO:
	return true;
}
