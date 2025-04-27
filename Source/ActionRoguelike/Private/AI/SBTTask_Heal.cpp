// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (ensure(MyPawn))
		{
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
			if (AttributeComp)
			{
				AttributeComp->ApplyHealthChange(MyPawn, 100); // Give AI max health
				return EBTNodeResult::Succeeded;	
			}
		}
	}
	return EBTNodeResult::Failed;	
}
