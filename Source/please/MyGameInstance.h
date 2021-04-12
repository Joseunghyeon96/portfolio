// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterData() : Level(1), Exp(1), STR(1), DEF(1) {}

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DEF;
};

USTRUCT(BlueprintType)
struct FPotionData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPotionData() : Name(" "),HealAmount(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 HealAmount;
};


UCLASS()
class PLEASE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		UMyGameInstance();

		virtual void Init() override;
		FCharacterData* GetCharacterData(int32 _Level);
		FPotionData* GetPotionData(int32 _Code);
private:
	UPROPERTY()
		class UDataTable* CharacterDataTable;
	UPROPERTY()
		class UDataTable* PotionDataTable;
		

	UPROPERTY()
		int32 MaxLevel;
};
