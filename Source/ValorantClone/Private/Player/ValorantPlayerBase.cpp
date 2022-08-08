// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ValorantPlayerBase.h"

// Sets default values
AValorantPlayerBase::AValorantPlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called to bind functionality to input
void AValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when the game starts or when spawned
void AValorantPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AValorantPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



