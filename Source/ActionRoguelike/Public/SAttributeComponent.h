// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, USAttributeComponent*, OwningComp, AActor*, InstigatorActor, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// EditAnywhere - edit in BP editor and per-instance in level.
	// VisibleAnywhere - read-only in editor and level (used for components)
	// EditDefaultsOnly - hide variable per-instance, edit only in BP editor
	// VisibleDefaultsOnly - read-only access for variable, only in BP editor
	// EditInstanceOnly - allow only editing of instance (when placed in level)
	// --
	// BlueprintReadOnly - read-only in Blueprint scripting (can still edit in details)
	// BlueprintReadWrite - can edit variable in scripting AND details panel
	// BlueprintAssignable - lets us subscribe/bind events (dispatcher)
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

public:

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float Delta);
	
};
