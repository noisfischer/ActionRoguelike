// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;
	
	UFUNCTION()
	void OnHealthChanged( USAttributeComponent* OwningComp, AActor* InstigatorActor, float NewHealth, float Delta);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	virtual void PostInitializeComponents() override;

	void SetTargetActor(AActor* NewTarget);

public:
	UFUNCTION(BlueprintCallable, Category="Attributes")
	FORCEINLINE USAttributeComponent* GetAttributeComponent() const { return AttributeComp; };

};
