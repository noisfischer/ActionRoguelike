// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickup.h"

// Sets default values
ASPickup::ASPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ASPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
	
	if (bIsActive)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		bIsActive = false;
		
		GetWorldTimerManager().SetTimer(ActiveReset, this, &ASPickup::Reactivate, ResetTime, false, -1);
	}
}

void ASPickup::Reactivate()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	bIsActive = true;
}

