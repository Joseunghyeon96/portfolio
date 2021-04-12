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
	FString WeaponName;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FString> Inventory;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 Level;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 Exp;
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
	
};
