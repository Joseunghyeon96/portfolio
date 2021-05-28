// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Forgeking_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API UBTService_Forgeking_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Forgeking_Detect();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DetectRadius;
};
