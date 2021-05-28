// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ForgeKing_FourStrike.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UBTTask_ForgeKing_FourStrike : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	bool bIsAttacking;
public:
	UBTTask_ForgeKing_FourStrike();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
