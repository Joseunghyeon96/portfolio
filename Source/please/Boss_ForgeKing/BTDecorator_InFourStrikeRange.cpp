// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_InFourStrikeRange.h"
#include "Boss_ForgeKing.h"
#include "ForgeKingController.h"
#include "../MyCharacter/Main.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_InFourStrikeRange::UBTDecorator_InFourStrikeRange()
{
	NodeName = TEXT("CanFourStrike");
	AttackRange = 200.f;
}

bool UBTDecorator_InFourStrikeRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
