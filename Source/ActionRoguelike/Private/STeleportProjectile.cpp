// Fill out your copyright notice in the Description page of Project Settings.

#include "STeleportProjectile.h"

ASTeleportProjectile::ASTeleportProjectile() : ASMagicProjectile()
{
	DestructionTime = 1.1f;
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

void ASTeleportProjectile::Teleport()
{
	AActor* Player = GetInstigator();
	Player->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0));
}


