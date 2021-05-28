// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ForgeKing_FindPatrolPos.h"
#include "ForgeKingController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ForgeKing_FindPatrolPos::UBTTask_ForgeKing_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}
EBTNodeResult::Type UBTTask_ForgeKing_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(controllingPawn->GetWorld());
	if(navSystem == nullptr)
		return EBTNodeResult::Failed;

	FVector origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AForgeKingController::HomePosKey);
	FNavLocation nextPatrol;
	if (navSystem->GetRandomPointInNavigableRadius(origin, 800.f, nextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AForgeKingController::PatrolPosKey, nextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
