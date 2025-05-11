// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::SetCredits(float Delta)
{
	Credits += Delta;
	if (Credits < 0.0f)
	{
		Credits = 0.0f;
	}

	OnCreditsChanged.Broadcast(this, Credits);	// for updating UI

	UE_LOG(LogTemp, Log, TEXT("%f credits awarded to: %s"), Delta, *GetNameSafe(this));
}
