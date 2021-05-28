// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgeKingAnimInstance.h"
#include "Boss_ForgeKing.h"

void UForgeKingAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			ForgeKing = Cast<ABoss_ForgeKing>(Pawn);
		}
	}
}


void UForgeKingAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			ForgeKing = Cast<ABoss_ForgeKing>(Pawn);
		}
	}

	if (ForgeKing)
	{
		FVector speed = Pawn->GetVelocity();
		FVector lateralSpeed = FVector(speed.X, speed.Y, 0.f);
		MovementSpeed = lateralSpeed.Size();
	}


}

