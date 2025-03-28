// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Chaos/ChaosPerfTest.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	HitEffect = CreateDefaultSubobject<UParticleSystemComponent>("HitEffect");
	HitEffect->SetAutoActivate(false);
	HitEffect->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
}


// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMagicProjectile::OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	EffectComp->SetVisibility(false);
	HitEffect->Activate(true);
	GetWorldTimerManager().SetTimer(DestructionTimer, this, &ASMagicProjectile::DestroyProjectile, DestructionTime);

}

void ASMagicProjectile::OnActorOverlap(class UPrimitiveComponent* MyComp, AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int Body, bool Sweep, const FHitResult& Hit)
{
	if (OtherActor && OtherActor!= GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);
		}
	}
}

void ASMagicProjectile::DestroyProjectile()
{
	Destroy();
}
