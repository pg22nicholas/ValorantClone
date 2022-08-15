// Copyright (C) Nicholas Johnson 2022
#include "ability/GroundIndicator.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGroundIndicator::AGroundIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AGroundIndicator::BeginPlay()
{
	Super::BeginPlay();
	StartIndicator();
}

void AGroundIndicator::StartIndicator()
{
	if (IsChargeable)
	{
		CurrLength = 0;
		GetWorld()->GetTimerManager().SetTimer(ChargeTimerHandle, this, &AGroundIndicator::IndicatorReachedMax, Length, false);
	}
	else
	{
		CurrLength = Length;
	}
}

// Called every frame
void AGroundIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrLength += DeltaTime;
}

void AGroundIndicator::EndIndicator()
{
	EndIndicatorDelegate.ExecuteIfBound(UKismetMathLibrary::Min(Length, CurrLength / Length));
	Destroy();
}

void AGroundIndicator::CancelIndicator()
{
	CancelIndicatorDelegate.ExecuteIfBound();
	Destroy();
}

void AGroundIndicator::IndicatorReachedMax()
{
	// Only perform end of ability if checked as automatically ending
	if (IsAutomaticEndAtMaxLength)
	{
		EndIndicator();
	}
}





