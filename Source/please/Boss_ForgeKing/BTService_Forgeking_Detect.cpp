// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Forgeking_Detect.h"
#include "ForgeKingController.h"
#include "Boss_ForgeKing.h"
#include "../MyCharacter/Main.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Forgeking_Detect::UBTService_Forgeking_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Forgeking_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* controllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr) return;

	UWorld* world = controllingPawn->GetWorld();
	FVector center = controllingPawn->GetActorLocation();

	if (world == nullptr) return;
	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams collisionQueryParam(NAME_None, false, controllingPawn);
	bool bResult = world->OverlapMultiByChannel(
		overlapResults,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		collisionQueryParam
	);
	
	ABoss_ForgeKing* boss = Cast<ABoss_ForgeKing>(controllingPawn);

	if (bResult)
	{
		for (auto overlapResult : overlapResults)
		{
			AMain* main = Cast<AMain>(overlapResult.GetActor());
			if (main)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AForgeKingController::TargetKey, main);
				if (boss)
				{
					boss->bHasValidTarget = true;
					boss->MainTarget = main;
				}
				DrawDebugSphere(world, center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(world, main->GetActorLocation(), 10.f, FColor::Blue, false, 0.2f);
				DrawDebugLine(world, controllingPawn->GetActorLocation(), main->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}

	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AForgeKingController::TargetKey, nullptr);
		if (boss)
		{
			boss->bHasValidTarget = false;
			boss->MainTarget = nullptr;
		}
	}
	DrawDebugSphere(world, center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
