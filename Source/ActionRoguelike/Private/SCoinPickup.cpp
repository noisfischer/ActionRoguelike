// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickup.h"

#include "SCharacter.h"
#include "SPlayerState.h"

ASCoinPickup::ASCoinPickup()
{
	CreditValue = 20.0f;
}

void ASCoinPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	ASCharacter* Character = Cast<ASCharacter>(InstigatorPawn);
	ASPlayerState* PlayerState = Cast<ASPlayerState>(Character->GetPlayerState());

	if (Character && PlayerState)
	{
		PlayerState->SetCredits(CreditValue);
		Super::Interact_Implementation(InstigatorPawn);	// hides and activates cooldown  timer
	}
}
