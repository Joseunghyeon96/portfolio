// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Item.h"
#include "../Potion.h"
#include "Weapon.h"
#include "Main.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory.Init(nullptr, 24);
	PotionActionBar.Init(nullptr, 6);
	// ...
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UInventoryComponent::AddToInventory(AItem* _Item)
{
	if (_Item == nullptr) return;

	if (_Item->Type == EItemType::ItemType_Equip)
	{
		int32 index = Inventory.IndexOfByPredicate([](AItem* item) {
			return  item == nullptr; });
		Inventory[index] = _Item;
	}

	else if (_Item->Type == EItemType::ItemType_Potion)
	{
		int32 index = Inventory.IndexOfByPredicate([_Item](AItem* item) {
			return item != nullptr && item->Name == _Item->Name; });
		if (index>-1 && index<Inventory.Num())
		{
			APotion* potion = Cast<APotion>(Inventory[index]);
			if (potion)
				potion->Amount++;
			_Item->Destroy();
		}
		else
		{
			int32 index2 = Inventory.IndexOfByPredicate([](AItem* item) {
				return  item == nullptr; });
			Inventory[index2] = _Item;
		}
	}

	DelUpdateInventory.Broadcast(Inventory);

	return;
}
int32 UInventoryComponent::DeleteToInventory(AItem* _Item)
{
	UE_LOG(LogTemp, Warning, TEXT("inven delete item func"));
	int32 index = Inventory.IndexOfByPredicate([_Item](AItem* item) {
		return item == _Item; });
	Inventory[index] = nullptr;
	DelUpdateInventory.Broadcast(Inventory);
	return index;
}

void UInventoryComponent::InventoryItemSwap(int32 _Idx1, int32 _Idx2)
{
	if (_Idx1<0 || _Idx1>Inventory.Num() ||
		_Idx2<0 || _Idx2>Inventory.Num())
		return;

	Inventory.Swap(_Idx1, _Idx2);
	DelUpdateInventory.Broadcast(Inventory);
}
void UInventoryComponent::AddToQuickSlot(int32 _DestIdx, int32 _SrcIdx)
{
	APotion* potion = Cast<APotion>(Inventory[_SrcIdx]);
	if (potion)
	{
		PotionActionBar[_DestIdx] = potion;
	}
	DelUpdatePotionActionBar.Broadcast(PotionActionBar);
}
void UInventoryComponent::QuickSlotItemSwap(int32 _Idx1, int32 _Idx2)
{
	if (_Idx1<0 || _Idx1>PotionActionBar.Num() ||
		_Idx2<0 || _Idx2>PotionActionBar.Num())
		return;

	PotionActionBar.Swap(_Idx1, _Idx2);
	DelUpdatePotionActionBar.Broadcast(PotionActionBar);
}
void UInventoryComponent::EquipWeapon1(AWeapon * _Weapon)
{
	if (_Weapon == nullptr) return;

	Weapon = _Weapon;
	DelUpdateWeapon.Broadcast(Weapon);
}

void UInventoryComponent::UnEquipWeapon(AWeapon* _Weapon)
{
	if (_Weapon == nullptr) return;

	if (Weapon == _Weapon)
	{
		Weapon = nullptr;
	}
	DelUpdateWeapon.Broadcast(Weapon);
}