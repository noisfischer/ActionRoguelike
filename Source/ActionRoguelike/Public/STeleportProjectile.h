// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:
	ASTeleportProjectile();

protected:

	FTimerHandle TeleportTimer;

	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float DetonateDelay;

	virtual void Explode_Implementation() override;

	void Teleport();
	
	virtual void OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void BeginPlay() override;
	
};
