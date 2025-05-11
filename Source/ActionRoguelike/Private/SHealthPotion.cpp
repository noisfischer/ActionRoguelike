// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"

ASHealthPotion::ASHealthPotion()
{
	CreditCost = 20.0f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	ASCharacter* Character = Cast<ASCharacter>(InstigatorPawn);
	ASPlayerState* PlayerState = Cast<ASPlayerState>(Character->GetPlayerState());

	if (AttributeComp && PlayerState)
	{
		if (PlayerState->GetCredits() >= CreditCost)
		{
			if (AttributeComp->GetCurrentHealth() != AttributeComp->GetMaxHealth())
			{
				Super::Interact_Implementation(InstigatorPawn);
				AttributeComp->ApplyHealthChange(this, HealthUp);
				PlayerState->SetCredits(-CreditCost);
			}
		}
	}
}
