// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgeKingController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AForgeKingController::HomePosKey(TEXT("HomePos"));
const FName AForgeKingController::PatrolPosKey(TEXT("PatrolPos"));
const FName AForgeKingController::TargetKey(TEXT("Target"));

AForgeKingController::AForgeKingController()
{
}

void AForgeKingController::OnPossess(APawn * _InPawn)
{
	Super::OnPossess(_InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, _InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("boss couldn't run BT"));
		}
	}
}
