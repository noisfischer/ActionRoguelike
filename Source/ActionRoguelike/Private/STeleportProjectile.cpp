// Fill out your copyright notice in the Description page of Project Settings.

#include "STeleportProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile() : ASBaseProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.0f;
	MovementComp->ProjectileGravityScale = 1.0f;
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &ASTeleportProjectile::Explode, DetonateDelay);
}


void ASTeleportProjectile::OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor,
                                 class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(MyComp, OtherActor, OtherComp, NormalImpulse, Hit);

	if (OtherActor != GetInstigator())
	{
		GetWorldTimerManager().SetTimer(TeleportTimer, this, &ASTeleportProjectile::Teleport, 0.2f);
	}
}

void ASTeleportProjectile::Explode_Implementation()
{
	// Super::Explode_Implementation();
	
	GetWorldTimerManager().ClearTimer(TeleportTimer);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASTeleportProjectile::Teleport, TeleportDelay);
}

void ASTeleportProjectile::Teleport()
{
	AActor* Player = GetInstigator();
	if (ensure(Player))
	{
		Player->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0));
	}
}


