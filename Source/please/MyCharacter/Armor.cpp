// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"
#include "Main.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundCue.h"
#include "MainStatManager.h"
#include "Kismet/GameplayStatics.h"

#define FloatToString(input) (FString::SanitizeFloat(input))

AArmor::AArmor()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
	Type = EItemType::ItemType_Equip;
	EAT = EArmorType::EAT_NONE;
}
void AArmor::BeginPlay()
{
	Super::BeginPlay();

	TypeTooltip = Korean(방어구 아이템);
	ItemTooltip += "DEF : " + FloatToString(DEF) + "\n" + ArmorTooltip;
}

void AArmor::Equip(AMain * Character)
{
	if (!Character) return;

	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetSimulatePhysics(false);

	OwnerCharacter = Character;
}

void AArmor::UseItem(AMain * _Main)
{
	if (_Main == nullptr) return;
	if (_Main->GetArmor(EAT) == this) return;

	UE_LOG(LogTemp, Warning, TEXT("weapon useitem func"));
	Super::UseItem(_Main);
	_Main->EquipArmor(this);
	_Main->GetStatManager()->AddDEF(DEF);
}

void AArmor::UnEquip(AMain* Character)
{
	if (!Character || OwnerCharacter != Character) return;
	OwnerCharacter = nullptr;
	Character->GetStatManager()->AddDEF(-DEF);
}
