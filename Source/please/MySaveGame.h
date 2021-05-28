// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Health;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Stamina;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 coins;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector Location;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FString> Inventory;

	//키 = 아이템이름 밸류 = 아이템 타입 1무기2방어구
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<FString, uint8> EqippedItemMap;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 Level;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 Exp;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 QuickIdx;
};
/**
 * 
 */
UCLASS()
class PLEASE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMySaveGame();

	UPROPERTY(VisibleAnywhere,Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIdx;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FCharacterStats CharacterStats;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool bIsSaved;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool bIsSwitch;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FName LevelName;
	
};
