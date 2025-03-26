// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SBlackholeProjectile.generated.h"

class URadialForceComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlackholeProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
public:
	ASBlackholeProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* ForceComp;

	UPROPERTY(EditAnywhere)
	float Duration = 5.0f;
	
	FTimerHandle TimerHandle_BlackholeDuration;

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bSweepResult, const FHitResult& SweepHit);
	
	void BlackholeDuration_TimeElapsed();

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
