// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPickup : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickup();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Credits")
	float CreditValue = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Activate")
	float ResetTime = 10.0f;

	FTimerHandle ActiveReset;
	
	void Reactivate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bIsActive = true;

};
