// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100.0f;

	// ...
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(this, nullptr, Health, Delta);	// for updating UI

	return true;
}
