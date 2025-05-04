// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	// ...
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<USAttributeComponent>();
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

bool USAttributeComponent::Kill(AActor* Instigator)
{
	return ApplyHealthChange(Instigator, -MaxHealth);
}

bool USAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	
	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0, MaxHealth);

	OnHealthChanged.Broadcast(this, InstigatorActor, CurrentHealth, Delta);	// for updating UI

	return true;
}
