// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickup.h"
#include "SCoinPickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPickup : public ASPickup
{
	GENERATED_BODY()

public:
	ASCoinPickup();

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
