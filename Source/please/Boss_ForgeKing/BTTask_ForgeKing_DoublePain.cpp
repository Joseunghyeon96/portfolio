// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ForgeKing_DoublePain.h"
#include "ForgeKingController.h"
#include "Boss_ForgeKing.h"

UBTTask_ForgeKing_DoublePain::UBTTask_ForgeKing_DoublePain()
{
	bNotifyTick = true;
	bIsAttacking = false;
	NodeName = TEXT("DoublePain");
}

EBTNodeResult::Type UBTTask_ForgeKing_DoublePain::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = Cast<ABoss_ForgeKing>(OwnerComp.GetAIOwner()->GetPawn());
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;

	controllingPawn->AttackDoublePain();
	bIsAttacking = true;

	controllingPawn->OnAttackEnd.AddLambda([this]()->void {
		bIsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_ForgeKing_DoublePain::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
