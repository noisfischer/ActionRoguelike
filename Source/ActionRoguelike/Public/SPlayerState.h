// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditsChanged, ASPlayerState*, OwningPlayer, float, CurrentCredits);
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetCredits(float Delta);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Credits")
	float Credits = 0.0f;

public:
	UPROPERTY(BlueprintAssignable, Category="Credits")
	FOnCreditsChanged OnCreditsChanged;

	FORCEINLINE float GetCredits() const { return Credits; }
};
