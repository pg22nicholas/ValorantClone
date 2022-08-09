// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyValorantPlayerBase.h"

void AMyValorantPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AValorantPlayerBase::Shoot); 

}
