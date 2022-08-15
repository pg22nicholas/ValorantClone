// Copyright (C) Nicholas Johnson 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundIndicator.generated.h"

UCLASS(Abstract)
class VALORANTCLONE_API AGroundIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundIndicator();

	DECLARE_DELEGATE(FCancelIndicatorSignature)
	FCancelIndicatorSignature CancelIndicatorDelegate;

	DECLARE_DELEGATE_OneParam(FEndIndicatorSignature, float)
	FEndIndicatorSignature EndIndicatorDelegate;

protected:
	
	virtual void EndIndicator();
	virtual void CancelIndicator();

	void IndicatorReachedMax();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Length = 3.f;

	float CurrLength;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsCharging = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsAutomaticEndAtMaxLength = true;
	  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsChargeable = true;

	FTimerHandle ChargeTimerHandle;

	virtual void StartIndicator();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
