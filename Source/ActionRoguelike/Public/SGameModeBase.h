// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

struct FEnvQueryResult;
class UEnvQuery;
class UCurveFloat;
class ASPlayerState;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;

	UFUNCTION()
	void SpawnBotTimerElapsed();
	
	void OnBotSpawnQueryCompleted(TSharedPtr<FEnvQueryResult> Result);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
public:
	ASGameModeBase();

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
	virtual void StartPlay() override;

	UFUNCTION(Exec)	// console command
	void KillAll();
	
};
