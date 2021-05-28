// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateWeaponDelegate, AWeapon*, _Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHeadDelegate, AArmor*, _Head);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateChestDelegate, AArmor*, _Chest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePantDelegate, AArmor*, _Pant);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateShoesDelegate, AArmor*, _Shoes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateShieldDelegate, AArmor*, _Shield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<AItem*>&, _Inventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePotionActionBarDelegate,const TArray<APotion*>&, _PotionActionBar);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<class AItem*> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<class APotion*> PotionActionBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag")
		int32 DragPressIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AArmor* Head;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AArmor* Chest;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AArmor* Pant;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AArmor* Shoes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class AArmor* Shield;
	
public:

	void AddToInventory(class AItem* _Item);
	int32 DeleteToInventory(class AItem* _Item);

	void EquipWeapon1(class AWeapon* _Weapon);
	void UnEquipWeapon(class AWeapon* _Weapon);

	void EquipHead(class AArmor* _Armor);
	void EquipChest(class AArmor* _Armor);
	void EquipPant(class AArmor* _Armor);
	void EquipShoes(class AArmor* _Armor);
	void EquipShield(class AArmor* _Armor);

	void UnEquipHead(class AArmor* _Armor);
	void UnEquipChest(class AArmor* _Armor);
	void UnEquipPant(class AArmor* _Armor);
	void UnEquipShoes(class AArmor* _Armor);
	void UnEquipShield(class AArmor* _Armor);


	UFUNCTION(BlueprintCallable)
		void InventoryItemSwap(int32 _Idx1, int32 _Idx2);

	UFUNCTION(BlueprintCallable)
		void AddToQuickSlot(int32 _DestIdx, int32 _SrcIdx);

	UFUNCTION(BlueprintCallable)
		void QuickSlotItemSwap(int32 _Idx1, int32 _Idx2);

	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateWeaponDelegate DelUpdateWeapon;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateHeadDelegate DelUpdateHead;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateChestDelegate DelUpdateChest;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdatePantDelegate DelUpdatePant;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateShoesDelegate DelUpdateShoes;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateShieldDelegate DelUpdateShield;
	UPROPERTY(BlueprintAssignable, Category = "Items")
		FUpdateInventoryDelegate DelUpdateInventory;

	UPROPERTY(BlueprintAssignable, Category = "Action Bar")
		FUpdatePotionActionBarDelegate DelUpdatePotionActionBar;

};
