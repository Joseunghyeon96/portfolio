// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	FString characterDataPath = TEXT("/Game/Data/leveldata.leveldata");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER(*characterDataPath);
	if (DT_CHARACTER.Succeeded())
	{
		CharacterDataTable = DT_CHARACTER.Object;
	}
	MaxLevel = 5;

	FString potionDataPath = TEXT("/Game/Data/potiondata.potiondata");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_POTION(*potionDataPath);
	if (DT_POTION.Succeeded())
	{
		PotionDataTable = DT_POTION.Object;
	}
}
void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("level 3 exp : %d"), GetCharacterData(3)->Exp);
}

FCharacterData * UMyGameInstance::GetCharacterData(int32 _Level)
{
	return CharacterDataTable->FindRow<FCharacterData>(*FString::FromInt(_Level), TEXT(""));
}

FPotionData*  UMyGameInstance::GetPotionData(int32 _Code)
{
	return PotionDataTable->FindRow<FPotionData>(*FString::FromInt(_Code), TEXT(""));
}
