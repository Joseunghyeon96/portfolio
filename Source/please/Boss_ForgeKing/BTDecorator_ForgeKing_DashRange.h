// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ForgeKing_DashRange.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UBTDecorator_ForgeKing_DashRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DashRange;

	UBTDecorator_ForgeKing_DashRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const override;
};
