// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	ASAICharacter* AICharacter = Cast<ASAICharacter>(GetPawn());
	if (ensure(AICharacter))
	{
		GetBlackboardComponent()->SetValueAsFloat("CurrentHealth", AICharacter->GetAttributeComponent()->GetMaxHealth());
	}
}
