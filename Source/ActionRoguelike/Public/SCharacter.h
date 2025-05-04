// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USInteractionComponent;
class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class USAttributeComponent;
class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> SpellProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category="Attack")
	UParticleSystem* SpellCastVFX;
	
	void SpawnProjectile(TSubclassOf<AActor> Projectile);
	
	FTimerHandle TimerHandle_Attack;
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	
	void PrimaryAttack();
	void SecondaryAttack();
	void CastSpell();

	void PrimaryInteract();

	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();
	void CastSpell_TimeElapsed();

	UFUNCTION()
	void OnHealthChanged( USAttributeComponent* OwningComp, AActor* InstigatorActor, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)	// turns the function into a console command (developer cheat)
	void HealSelf(float Amount = 100);

};
