// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "Boss_ForgeKing.h"
#include "ForgeKingController.h"
#include "../MyCharacter/Main.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
	AttackRange = 200.f;
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr)
		return false;

	auto target = Cast<AMain>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AForgeKingController::TargetKey));
	if (target == nullptr)
		return false;

	bResult = (target->GetDistanceTo(controllingPawn) <= AttackRange);
	return bResult;
}
