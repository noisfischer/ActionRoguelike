// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensure(ProjectileClass))
	{
		FHitResult Hit;
		FVector StartLocation = InstigatorCharacter->GetPawnViewLocation();
		FVector EndLocation = StartLocation + InstigatorCharacter->GetControlRotation().Vector() * 10000;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(InstigatorCharacter);
	
		bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, StartLocation, EndLocation, ObjectQueryParams, CollisionParams);
	
		if (bBlockingHit)
		{
			EndLocation = Hit.ImpactPoint;
		}
		else
		{
			EndLocation = Hit.TraceEnd;
		}

		FVector SpawnLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, EndLocation);
		FTransform SpawnTM = FTransform(SpawnRotation,SpawnLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;
	
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, InstigatorCharacter->GetMesh(), FName(HandSocketName), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
	}

	StopAction(InstigatorCharacter);
}
