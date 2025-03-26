// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASBlackholeProjectile::ASBlackholeProjectile() : ASMagicProjectile()
{
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->Radius = 1000.0f;
	ForceComp->ForceStrength = -1000000.0f;
	ForceComp->ImpulseStrength = 0.0f;
	ForceComp->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery3); // Ignores pawn objects
	ForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	ForceComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackholeProjectile::OnOverlap);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	MovementComp->MaxSpeed = 1000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
}


void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_BlackholeDuration, this, &ASBlackholeProjectile::BlackholeDuration_TimeElapsed, Duration);
}


void ASBlackholeProjectile::OnOverlap(class UPrimitiveComponent* MyComp, AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bSweepResult, const FHitResult& SweepHit)
{
	if (OtherActor->GetRootComponent()->IsSimulatingPhysics())
	{
		FString CombinedString = FString::Printf(TEXT("DESTROYED ACTOR: %s"), *GetNameSafe(OtherActor));
		DrawDebugString(GetWorld(), GetActorLocation(), CombinedString, NULL, FColor::White, 2.0f, true);
		OtherActor->Destroy();
	}
}

void ASBlackholeProjectile::BlackholeDuration_TimeElapsed()
{
	Destroy();
}

void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForceComp->FireImpulse();
}
