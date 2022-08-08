// Fill out your copyright notice in the Description page of Project Settings.


#include "ability/GroundIndicator.h"

// Sets default values
AGroundIndicator::AGroundIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroundIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

