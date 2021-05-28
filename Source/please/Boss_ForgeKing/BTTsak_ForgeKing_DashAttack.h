// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTsak_ForgeKing_DashAttack.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UBTTsak_ForgeKing_DashAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
private: 
	bool bIsAttacking;
public:
	UBTTsak_ForgeKing_DashAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds) override;

};

