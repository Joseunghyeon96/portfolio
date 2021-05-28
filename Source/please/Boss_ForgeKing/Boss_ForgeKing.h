// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Enemy/Enemy.h"
#include "Boss_ForgeKing.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDashEndDelegate);
/**
 * 
 */

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	AttackType_Default UMETA(DisplayName = "Default"),
	AttackType_Dash UMETA(DisplayName = "Dash"),
	AttackType_FourStrike UMETA(DisplayName = "FourStrike"),
	AttackType_DoublePain UMETA(DisplayName = "DoublePain"),

	AttackType_Max UMETA(DisplayName = "Max")
};


UCLASS()
class PLEASE_API ABoss_ForgeKing : public AEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		bool bDashAttack1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsAttackFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName TransitionLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DashSpeed;

	EAttackType EAT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UBoxComponent* LeftCombatCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DashAttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoublePainSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* FourStrikeSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ABoss_ForgeKing();

	virtual void Tick(float DeltaTime) override;

	virtual void DectectableSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void DectectableSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	UFUNCTION()
	void LeftCombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void LeftCombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void AttackEnd() override;

	FOnAttackEndDelegate OnAttackEnd;
	FOnDashEndDelegate OnDashEnd;


	virtual void ActivateCollision() override;
	virtual void DeactivateCollision() override;

	UFUNCTION(BlueprintCallable)
	void LeftActivateCollision();

	UFUNCTION(BlueprintCallable)
	void RightActivateCollision();

	void SetEAT(EAttackType _Input);
	void SkillDash();
	UFUNCTION(BlueprintCallable)
	void SkillDashEnd();
	void SkillDashAttack();
	void AttackDoublePain();
	void FourStrike();

	void OpenClear();
	virtual void DeathEnd() override;


};
