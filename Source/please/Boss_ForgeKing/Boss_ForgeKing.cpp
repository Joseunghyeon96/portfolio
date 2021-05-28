// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_ForgeKing.h"
#include "ForgeKingController.h"
#include "../MyCharacter/Main.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../pleaseGameModeBase.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetMathLibrary.h"

ABoss_ForgeKing::ABoss_ForgeKing()
{
	DashSpeed = 1;
	bIsAttackFrame = false;

	LeftCombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision2"));
	LeftCombatCollision->SetupAttachment(GetMesh(), FName("EnemySocket2"));

	DeathDelay = 5.0f;
}

void ABoss_ForgeKing::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AForgeKingController>(GetController());

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoss_ForgeKing::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &ABoss_ForgeKing::CombatOnOverlapEnd);

	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	LeftCombatCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoss_ForgeKing::LeftCombatOnOverlapBegin);
	LeftCombatCollision->OnComponentEndOverlap.AddDynamic(this, &ABoss_ForgeKing::LeftCombatOnOverlapEnd);

	LeftCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftCombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftCombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftCombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

}

void ABoss_ForgeKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDashAttack1)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector CurrentLocation = this->GetActorLocation();

		SetActorLocation(CurrentLocation + (Direction * DashSpeed));
	}
	//UE_LOG(LogTemp, Log, TEXT("Damage: %f"), Damage);

}


void ABoss_ForgeKing::DectectableSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Super::DectectableSphereOnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
void ABoss_ForgeKing::DectectableSphereOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//Super::DectectableSphereOnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void ABoss_ForgeKing::CombatSphereOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ABoss_ForgeKing::CombatSphereOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}

void ABoss_ForgeKing::CombatOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!IsAlive()) return;

	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		if (main) {
			if (main->GetDash())
				return;

			if (bIsAttackFrame) return;


			if (main->HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), main->HitParticles, OtherComp->GetComponentLocation(), FRotator(0.f), false);
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(main, Damage, AIController, this, DamageTypeClass);
			}
			bIsAttackFrame = true;
		}
	}
}

void ABoss_ForgeKing::CombatOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void ABoss_ForgeKing::LeftCombatOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!IsAlive()) return;

	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		if (main) {
			if (main->GetDash())
				return;

			if (bIsAttackFrame) return;


			if (main->HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), main->HitParticles, OtherComp->GetComponentLocation(), FRotator(0.f), false);
			}
			if (DamageTypeClass)
			{
				UGameplayStatics::ApplyDamage(main, Damage, AIController, this, DamageTypeClass);
			}
			bIsAttackFrame = true;
		}
	}
}

void ABoss_ForgeKing::LeftCombatOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void ABoss_ForgeKing::AttackEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("ForgeKing attack end"));
	bAttacking = false;
	bIsAttackFrame = false;
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Idle);
	SetEAT(EAttackType::AttackType_Default);
	OnAttackEnd.Broadcast();
}

void ABoss_ForgeKing::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

	GetWorldTimerManager().SetTimer(DeathTimer, this, &ABoss_ForgeKing::OpenClear, DeathDelay);
}
void ABoss_ForgeKing::OpenClear()
{
	AMain* main = Cast<AMain>(UGameplayStatics::GetPlayerCharacter(this,0));
	if (main)
	{
		main->SwitchLevel(TransitionLevelName);
	}

}

void ABoss_ForgeKing::ActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LeftCombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABoss_ForgeKing::DeactivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoss_ForgeKing::LeftActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftCombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABoss_ForgeKing::RightActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LeftCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoss_ForgeKing::SetEAT(EAttackType _Input)
{
	EAT = _Input;

	UE_LOG(LogTemp, Warning, TEXT("ForgeKing SetEAT "));

	switch (EAT)
	{
	case EAttackType::AttackType_Default:
		Damage = 15.;
		break;
	case EAttackType::AttackType_Dash:
		Damage = 25.f;
		break;
	case EAttackType::AttackType_FourStrike:
		Damage = 5.f;
		break;
	case EAttackType::AttackType_DoublePain:
		Damage = 20.f;
		break;

	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("ForgeKing dash "));

}

void ABoss_ForgeKing::SkillDash()
{
	if (!IsAlive()) return;

	if (AIController)
	{
		AIController->StopMovement();
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
	}

	if (!bAttacking)
	{
		SetEAT(EAttackType::AttackType_Dash);
		bDashAttack1 = true;
		bAttacking = true;

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), MainTarget->GetActorLocation());

		this->SetActorRotation(Rotator);

		UE_LOG(LogTemp, Warning, TEXT("ForgeKing dash "));
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance)
		{
			animInstance->Montage_Play(CombatMontage, 1);
			animInstance->Montage_JumpToSection(FName("Dash"), CombatMontage);
		}
	}
}
void ABoss_ForgeKing::SkillDashEnd()
{
	bDashAttack1 = false;
	SkillDashAttack();
}

void ABoss_ForgeKing::SkillDashAttack()
{
	if (!IsAlive()) return;

	if (AIController)
	{
		AIController->StopMovement();
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
	}

	if (!bDashAttack1)
	{
		UE_LOG(LogTemp, Warning, TEXT("ForgeKing dash attack"));
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance)
		{
			animInstance->Montage_Play(CombatMontage, 1);
			animInstance->Montage_JumpToSection(FName("DashAttack"), CombatMontage);
		}
		if(DashAttackSound)
			UGameplayStatics::PlaySound2D(this, DashAttackSound,GM->EffectVolume);
	}
}

void ABoss_ForgeKing::AttackDoublePain()
{
	if (!IsAlive()) return;

	if (AIController)
	{
		AIController->StopMovement();
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
	}

	if (!bAttacking)
	{
		bAttacking = true;
		SetEAT(EAttackType::AttackType_DoublePain);

		UE_LOG(LogTemp, Warning, TEXT("ForgeKing DoublePain"));
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance)
		{
			animInstance->Montage_Play(CombatMontage, 1);
			animInstance->Montage_JumpToSection(FName("DoublePain"), CombatMontage);
		}
		if (DoublePainSound)
			UGameplayStatics::PlaySound2D(this, DoublePainSound, GM->EffectVolume);
	}
}

void ABoss_ForgeKing::FourStrike()
{
	if (!IsAlive()) return;

	if (AIController)
	{
		AIController->StopMovement();
		SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
	}

	if (!bAttacking)
	{
		bAttacking = true;
		SetEAT(EAttackType::AttackType_FourStrike);
		UE_LOG(LogTemp, Warning, TEXT("ForgeKing FourStrike"));
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		if (animInstance)
		{
			animInstance->Montage_Play(CombatMontage, 1.5f);
			animInstance->Montage_JumpToSection(FName("FourStrike"), CombatMontage);
		}
		if (FourStrikeSound)
			UGameplayStatics::PlaySound2D(this, FourStrikeSound, GM->EffectVolume);
	}
}
