// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"
#include "../MyCharacter/Main.h"
#include "../MyCharacter/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameInstance.h"

#define FloatToString(input) (FString::SanitizeFloat(input))

APotion::APotion()
{
	Amount = 1;
	Type = EItemType::ItemType_Potion;
}

void APotion::BeginPlay()
{
	Super::BeginPlay();

	auto gameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	PotionData = gameInstance->GetPotionData(ItemCode);
	HealAmount = PotionData->HealAmount;
	Name = PotionData->Name;

	TypeTooltip = Korean(소비 아이템);
	ItemTooltip += TEXT("사용 시 ")+ FloatToString(HealAmount) + TEXT(" 만큼 체력을 회복합니다.");

}

void APotion::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (!OtherActor) return;

	AMain* main = Cast<AMain>(OtherActor);
	if (!main) return;

	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UGameplayStatics::ApplyDamage(OtherActor, -HealAmount, nullptr, this, DamageTypeClass);
	Destroy();

}

void APotion::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}

void APotion::UseItem(AMain * _Main)
{
	Super::UseItem(_Main);
	if (Amount < 1) return;

	UE_LOG(LogTemp, Warning, TEXT("potion useitem func"));
	UGameplayStatics::ApplyDamage(_Main, -HealAmount, nullptr, this, DamageTypeClass);
	Amount--;

	if (Amount < 1)
	{
		_Main->DeleteToItem(this);
		Destroy();
	}
	else
		_Main->GetInventory()->DelUpdateInventory.Broadcast(_Main->GetInventory()->Inventory);
}
