// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTsak_ForgeKing_DashAttack.h"
#include "ForgeKingController.h"
#include "Boss_ForgeKing.h"


UBTTsak_ForgeKing_DashAttack::UBTTsak_ForgeKing_DashAttack()
{
	bNotifyTick = true;
	bIsAttacking = false;
	NodeName = TEXT("DashAttack");
}
EBTNodeResult::Type UBTTsak_ForgeKing_DashAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = Cast<ABoss_ForgeKing>(OwnerComp.GetAIOwner()->GetPawn());
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	controllingPawn->SkillDash();
	bIsAttacking = true;

	controllingPawn->OnAttackEnd.AddLambda([this]()->void {
		bIsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTsak_ForgeKing_DashAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
