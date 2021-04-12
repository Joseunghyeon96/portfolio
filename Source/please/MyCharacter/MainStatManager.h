// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainStatManager.generated.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
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


		
};
