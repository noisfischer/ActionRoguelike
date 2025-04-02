// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp)
	{
		if (AttributeComp->GetCurrentHealth() != AttributeComp->GetMaxHealth())
		{
			Super::Interact_Implementation(InstigatorPawn);
			AttributeComp->ApplyHealthChange(HealthUp);
		}
	}
}
