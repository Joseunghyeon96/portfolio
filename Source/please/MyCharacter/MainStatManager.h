// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainStatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusUpdate, UMainStatManager*, StatManager);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASE_API UMainStatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainStatManager();
	friend class AMain;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	struct FCharacterData* StatData;

	/*
	Player Stats
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float DEF;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 Exp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float STR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float WeaponDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 LevelUpExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 MaxLevel;
public:	
	/*
	Player Stats
	*/

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ApplyExp(int32 _Exp);
	void AddWeaponDamage(float _InputDamage);
	void AddDEF(float _InputDEF);
	void AddSTR(float _InputSTR);
	void SetDamage();
	void LevelUp();
	FORCEINLINE float GetDamage() const { return Damage; }


	UPROPERTY(BlueprintAssignable, Category = "Update")
	FStatusUpdate DelStatUpdate;


		
};
