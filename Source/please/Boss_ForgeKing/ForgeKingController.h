// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ForgeKingController.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API AForgeKingController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "AI")
		class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBlackboardData* BBAsset;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
public:
	AForgeKingController();

	virtual void OnPossess(APawn* _InPawn) override;

};
