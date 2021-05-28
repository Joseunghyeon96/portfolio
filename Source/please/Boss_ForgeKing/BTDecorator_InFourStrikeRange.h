// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_InFourStrikeRange.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UBTDecorator_InFourStrikeRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackRange;

	UBTDecorator_InFourStrikeRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const override;
};
