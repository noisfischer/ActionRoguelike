// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	// ...
}

bool USAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0, MaxHealth);

	OnHealthChanged.Broadcast(this, nullptr, CurrentHealth, Delta);	// for updating UI

	return true;
}
