// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ForgeKing_FourStrike.h"
#include "ForgeKingController.h"
#include "Boss_ForgeKing.h"

UBTTask_ForgeKing_FourStrike::UBTTask_ForgeKing_FourStrike()
{
	bNotifyTick = true;
	bIsAttacking = false;
	NodeName = TEXT("FourStrike");
}

EBTNodeResult::Type UBTTask_ForgeKing_FourStrike::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = Cast<ABoss_ForgeKing>(OwnerComp.GetAIOwner()->GetPawn());
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;

	controllingPawn->FourStrike();
	bIsAttacking = true;

	controllingPawn->OnAttackEnd.AddLambda([this]()->void {
		bIsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_ForgeKing_FourStrike::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

