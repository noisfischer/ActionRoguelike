// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"

#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASBaseProjectile::OnHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("SoundComp");
	AudioComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 8000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	AudioComp->Play();
}

// Called every frame
void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBaseProjectile::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), 5000.0f, 10000.0f, 1, false);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, GetActorLocation(), GetActorRotation());
		AudioComp->Stop();
		Destroy();
	}
}

void ASBaseProjectile::OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor!= GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -20.0f);
		}
		EffectComp->SetVisibility(false);
		Explode();
	}
}

