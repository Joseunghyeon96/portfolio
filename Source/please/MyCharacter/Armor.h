// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Items/Item.h"
#include "Armor.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EArmorType : uint8 {
	EAT_NONE UMETA(DisplayName = "None"),
	EAT_Head UMETA(DisplayName = "Head"),
	EAT_Chest UMETA(DisplayName = "Chest"),
	EAT_Shield UMETA(DisplayName = "Shield"),
	EAT_Pant UMETA(DisplayName = "Pant"),
	EAT_Shoes UMETA(DisplayName = "Shoes"),

	EWS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class PLEASE_API AArmor : public AItem
{
	GENERATED_BODY()

public:
	AArmor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	EArmorType EAT;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character")
	class AMain* OwnerCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Stats")
	float DEF;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Tooltip")
	FString	ArmorTooltip;

protected:
	virtual void BeginPlay() override;
public:

	void Equip(class AMain* Character);
	void UseItem(class AMain* _Main) override;
	void UnEquip(class AMain* Character);
};
