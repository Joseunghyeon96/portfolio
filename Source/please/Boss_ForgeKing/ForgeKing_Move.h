// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ForgeKing_Move.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UForgeKing_Move : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UForgeKing_Move();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
