// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Armor.h"
#include "Main.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateItemBoxDelegate, const TArray<AItem*>&, Items);

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_Exhausted UMETA(DisplayName = "Exhausted"),
	EMS_Dead UMETA(DisplayName= "Dead"),

	EMS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class ESkillDamage : uint8
{
	ESD_Normal UMETA(DisplayName = "Normal"),
	ESD_Slash UMETA(DisplayName = "Slash"),

	ESD_MAX UMETA(DisplayName = "Normal"),
};

UCLASS()
class PLEASE_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameMode)
		class ApleaseGameModeBase* GM;

	UPROPERTY(EditDefaultsOnly, Category = "SavedData")
		TSubclassOf<class AItemStorage> WeaponStorage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		bool bCanComboAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		bool bDash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		bool bCanDash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		bool bComboCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		int32 CurrentCombo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
		int32 MaxCombo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	class AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items | Armor")
		class AArmor* ArmorHead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items | Armor")
		class AArmor* ArmorShoes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items | Armor")
		class AArmor* ArmorChest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items | Armor")
		class AArmor* ArmorPant;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items | Armor")
		class AArmor* ArmorShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	class AItem* ActiveOverlappingItem;

	// Movement Status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite , Category = "Enums")
	EMovementStatus MS;

	// Stamina Status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus ESS;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	ESkillDamage ESD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	// Camera boom positioning the camera behind the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//to scale turning functions for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	float RunningSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	float SprintingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bCanSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* SkillMontage;

	/*
	캐릭터 스텟 관리 매니저
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
		class UMainStatManager* StatManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		AController* WeaponInstigator;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	class UParticleSystem* HealParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* HealSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* DashSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* JumpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 Coins;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemy* CombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector DashLocation;

	bool bInterpToEnemy;

	FTimerHandle DashHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bDashCheck;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsFMoved;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsRMoved;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	class AItemBox* ItemBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UInventoryComponent* InventoryComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		TArray<class AItem*> TempInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ToolTip")
	FString HelpText;

	FTimerDelegate TextDel;
	FTimerHandle TextHandle;
	
	// 스킬 관련 생성 오브젝트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Skill")
		TSubclassOf<class AActor> FireBall;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called for forward or backward input
	void MoveForward(float value);
	// Called for side input
	void MoveRight(float value);
	void SetSprintRun(float value);
	virtual void Jump() override;
	virtual void StopJumping() override;

	// Called via input to turn at a given rate
	// @param rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	void TurnAtRate(float rate);
	// Called via input to look up/down at a given rate
	// @param rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
	void LookUpRate(float rate);

	UFUNCTION()
		void VariationCoin(int32 Amount);

	UFUNCTION()
		void Die();

	void TickStamina(float DeltaTime);
	void SetMovementStatus(EMovementStatus Input);
	void SetSprinting();
	void SetRunning();

	UFUNCTION(BlueprintCallable)
	void PressKeyF();
	void PressKeyG();
	void PressKeyH();
	FRotator GetLookAtRotationYaw(FVector TargetLocation);
	void Attack();
	void ComboAttack();
	UFUNCTION(BlueprintCallable)
	void ComboCheck();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void DashEnd();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();
	void DashCheck1();
	void DashCheck2();

	// 스킬 함수
	UFUNCTION(BlueprintCallable)
		void CastingSpell(int32 _SpellNum);
	UFUNCTION(BlueprintCallable)
		void Skill_SlashAttack(); // 1번 스킬
	UFUNCTION(BlueprintCallable)
		void Skill_Fireball(); // 2번 스킬
	UFUNCTION(BlueprintCallable)
		void SpawnFireBall(); // 2번에 필요


	UFUNCTION()
	void Dash();
	void SetInterpToEnemy(bool Interp);
	void SimpleTakeDamage(float DamageAmount);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	void SwitchLevel(FName LevelName);
	
	void UseQuickSlotItem(int32 _Idx);

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame(bool SetPosition);

	void MainApplyDamage(class AEnemy* _Enemy, TSubclassOf<UDamageType> _DamageTypeClass );
	void ApplyMagicDamage(class AEnemy* _Enemy, TSubclassOf<UDamageType> _DamageTypeClass,float Damage);
	
	UFUNCTION(BlueprintCallable)
	void ESCDown();

	bool CanMove();
	UFUNCTION(BlueprintCallable)
	void OpenItemBox();

	UPROPERTY(BlueprintAssignable, Category = "Items")
	FUpdateItemBoxDelegate DelOpenItemBox;

	UFUNCTION(BlueprintCallable)
	void AddToItem(class AItem* _Item);
	UFUNCTION(BlueprintCallable)
	void DeleteToItem(class AItem* _Item);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(class AItem* Item);
	UFUNCTION(BlueprintCallable)
	void UnEquipWeapon(AItem* _Item);

	UFUNCTION(BlueprintCallable)
	void EquipArmor(class AItem* Item);
	UFUNCTION(BlueprintCallable)
	void UnEquipArmor(AItem* _Item);

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	void OpenInventory();

	UFUNCTION(BlueprintCallable)
	void ShowHelpString(FString Text);

	AArmor* GetArmor(enum class EArmorType ArmorType);

	void SetItemBox(AItemBox* Target);
	FORCEINLINE void SetStaminaStatus(EStaminaStatus Input) { ESS = Input; }
	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }
	FORCEINLINE bool GetDash() { return bDash; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet) { EquippedWeapon = WeaponToSet; }
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }
	FORCEINLINE class UMainStatManager* GetStatManager() const{ return StatManager; }
	FORCEINLINE class UInventoryComponent* GetInventory() const{ return InventoryComp; }

};
