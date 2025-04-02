// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UAudioComponent;
class USoundBase;

UCLASS(ABSTRACT) // 'ABSTRACT' marks this class as incomplete, keeping it out certain dropdown windows like SpawnActor in the editor
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USoundBase* ImpactSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TSubclassOf<class UCameraShakeBase> CameraShake;
	
	UFUNCTION()
	virtual void OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
