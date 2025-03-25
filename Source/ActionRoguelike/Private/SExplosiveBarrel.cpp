// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	BarrelMesh->SetCollisionObjectType(ECC_PhysicsBody);
	BarrelMesh->SetSimulatePhysics(true);
	RootComponent = BarrelMesh;
	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 500.0f;
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->SetupAttachment(BarrelMesh);

}

void ASExplosiveBarrel::OnHit(class UPrimitiveComponent* MyComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	
	// LOGGING NOTES
	 
	UE_LOG(LogTemp, Log, TEXT("EXPLOSION!!!"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds); // * does a conversion
	
	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, NULL, FColor::White, 2.0f, true);
	
}

	
// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

