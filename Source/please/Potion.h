// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API APotion : public AItem
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heal")
		int32 HealAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Heal")
		int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UDamageType> DamageTypeClass;

	struct FPotionData* PotionData;

protected:
	virtual void BeginPlay() override;

public:
	APotion();


	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void UseItem(class AMain* _Main) override;
};
