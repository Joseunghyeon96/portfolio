// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgeKing_Move.h"
#include "ForgeKingController.h"
#include "Boss_ForgeKing.h"
#include "../MyCharacter/Main.h"
#include "BehaviorTree/BlackboardComponent.h"

UForgeKing_Move::UForgeKing_Move()
{
	NodeName = TEXT("MoveToMain");
}
EBTNodeResult::Type UForgeKing_Move::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = Cast<ABoss_ForgeKing>(OwnerComp.GetAIOwner()->GetPawn());
	if (controllingPawn == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("boss move :: boss nullptr"));
		return EBTNodeResult::Failed;
	}

	auto main = Cast<AMain>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AForgeKingController::TargetKey));
	if (main == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("boss move :: target nullptr"));
		return EBTNodeResult::Failed;
	}
	controllingPawn->MoveToTarget(main);
	//UE_LOG(LogTemp, Warning, TEXT("boss move :: success "));

	return EBTNodeResult::Succeeded;
}
