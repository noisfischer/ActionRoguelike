// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASMagicProjectile
{
	GENERATED_BODY()

public:
	ASTeleportProjectile();

protected:

	FTimerHandle TeleportTimer;

	void Teleport();
	
	virtual void OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;


	
};
