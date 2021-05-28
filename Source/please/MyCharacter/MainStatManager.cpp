// Fill out your copyright notice in the Description page of Project Settings.


#include "MainStatManager.h"
#include "../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Main.h"

// Sets default values for this component's properties
UMainStatManager::UMainStatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 100.f;
	CurrentHealth = 100.f;
	MaxStamina = 200.f;
	CurrentStamina = 100.f;
	Exp = 1;
	Level = 1;
	Damage = 0.f;
	MaxLevel = 5;
}


// Called when the game starts
void UMainStatManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	StatData = gameInstance->GetCharacterData(Level);
	LevelUpExp = StatData->Exp;
	DelStatUpdate.Broadcast(this);
}

void UMainStatManager::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UMainStatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMainStatManager::ApplyExp(int32 _Exp)
{
	UE_LOG(LogTemp, Warning, TEXT("Apply Exp func"));

	if (StatData != nullptr)
	{
		Exp += _Exp;
		if (LevelUpExp <= Exp)
		{
			if (Level == MaxLevel)
			{
				Exp = LevelUpExp;
			}
			else {
				auto gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				StatData = gameInstance->GetCharacterData(Level);
				LevelUp();
			
			}
		}
	}
}

void UMainStatManager::AddWeaponDamage(float _InputDamage)
{
	WeaponDamage += _InputDamage;
	SetDamage();
}

void UMainStatManager::AddDEF(float _InputDEF)
{
	DEF += _InputDEF;
	DelStatUpdate.Broadcast(this);
}
void UMainStatManager::AddSTR(float _InputSTR)
{
	STR += _InputSTR;
	SetDamage();
	DelStatUpdate.Broadcast(this);
}
void UMainStatManager::LevelUp()
{
	Level++;
	Exp -= LevelUpExp;
	LevelUpExp = StatData->Exp;
	AddSTR(StatData->STR);
	DelStatUpdate.Broadcast(this);
}
void UMainStatManager::SetDamage()
{
	Damage = WeaponDamage + STR;
	DelStatUpdate.Broadcast(this);
}
