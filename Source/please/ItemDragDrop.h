// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDrop.generated.h"

enum EItemType;
/**
 * 
 */
UCLASS()
class PLEASE_API UItemDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int FrontSlotIndex;

	// �������� �κ��丮���� �������� true // �ƴϸ� false(������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		bool DragInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> Type;
};
