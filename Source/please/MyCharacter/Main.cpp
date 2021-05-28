
// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "../Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon.h"
#include "../Items/Potion.h"
#include "../MySaveGame.h"
#include "../pleaseGameModeBase.h"
#include "../Items/ItemBox.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerController.h"
#include "MainStatManager.h"
#include "Skill_FireBallObject.h"
#include "InventoryComponent.h"
#include "../Items/ItemStorage.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Boom (pulls towards the player if there's a collision
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f; // Camera follow at this distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom , USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match
	// the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	//Set turn rates
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
	
	//Set speed
	RunningSpeed = 650.0f;
	SprintingSpeed = 950.0f;
	
	//Don't rotate when the controller rotates.
	//Let that just affect the camera.
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 460.0f;
	GetCharacterMovement()->AirControl = 0.3f;

	StatManager = CreateDefaultSubobject<UMainStatManager>(TEXT("Stat Manager"));
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	CurrentCombo = 1;
	MaxCombo = 2;
	bComboCheck = false;
	bCanComboAttack = false;
	Coins = 0;

	//Init Enums
	MS = EMovementStatus::EMS_Normal;
	ESS = EStaminaStatus::ESS_Normal;
	
	bCanSprint = true;
	StaminaDrainRate = 25.f;
	MinSprintStamina = 100.f;
	bCanDash = true;
	bDash = false;
	bIsFMoved = false;
	bIsRMoved = false;
	bDashCheck = false;

	InterpSpeed = 15.f;
	bInterpToEnemy = false;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation() + FVector(0, 0, 75.f), 25.f, 12, FLinearColor::Red, 10.f, 0.4f);
	MainPlayerController = Cast<AMainPlayerController>(GetController());
	WeaponInstigator = GetController();
	GM = Cast<ApleaseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LoadGame(false);
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MS == EMovementStatus::EMS_Dead) return;

	TickStamina(DeltaTime);

	if (bInterpToEnemy && CombatTarget)
	{
		FRotator lookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
		FRotator interpRotation = FMath::RInterpTo(GetActorRotation(), lookAtYaw, DeltaTime, InterpSpeed);
		SetActorRotation(interpRotation);
	}

	if (bDash)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), DashLocation, DeltaTime, 4.0f));
	}


}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//Camera Movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMain::ESCDown).bExecuteWhenPaused = true;
	//Character movement
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMain::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMain::StopJumping);
	PlayerInputComponent->BindAction("FKey", IE_Pressed, this, &AMain::PressKeyF);
	PlayerInputComponent->BindAction("IKey", IE_Pressed, this, &AMain::OpenInventory);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMain::ComboAttack);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMain::Attack);
	PlayerInputComponent->BindAction("GKey", IE_Pressed, this, &AMain::PressKeyG);
	PlayerInputComponent->BindAction("HKey", IE_Pressed, this, &AMain::PressKeyH);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMain::DashCheck1);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMain::Dash);
	PlayerInputComponent->BindAction("TempKey", IE_Released, this, &AMain::SaveGame);
	PlayerInputComponent->BindAction("RKey", IE_Released, this, &AMain::RestartLevel);

	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int32);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_1", IE_Released, this, &AMain::UseQuickSlotItem,0);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_2", IE_Released, this, &AMain::UseQuickSlotItem,1);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_3", IE_Released, this, &AMain::UseQuickSlotItem,2);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_4", IE_Released, this, &AMain::UseQuickSlotItem,3);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_5", IE_Released, this, &AMain::UseQuickSlotItem,4);
	InputComponent->BindAction<FCustomInputDelegate>("QuickSlot_6", IE_Released, this, &AMain::UseQuickSlotItem,5);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpRate);
	PlayerInputComponent->BindAxis("Sprint", this, &AMain::SetSprintRun);

}

void AMain::MoveForward(float value)
{
	if ((value == 0.f) || !CanMove())
	{
		bIsFMoved = false;
		return;
	}
	// Fine out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	bIsFMoved = true;

	if (bAttacking)
		AddMovementInput(Direction, 0);
	else
		AddMovementInput(Direction, value);
}


void AMain::MoveRight(float value)
{
	if (!CanMove() || (value == 0.f))
	{
		bIsRMoved = false;
		return;
	}
	// Fine out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	bIsRMoved = true;
	
	if(bAttacking)
		AddMovementInput(Direction, 0);

	else
		AddMovementInput(Direction, value);
}

void AMain::SetSprintRun(float value)
{
	if (value == 0)
		SetRunning();
	else
		SetSprinting();
}

void AMain::Jump()
{
	if (!CanMove() || bAttacking) return;

	ACharacter::Jump();
	UGameplayStatics::PlaySound2D(this, JumpSound, GM->EffectVolume);
}

void AMain::StopJumping()
{
	if (!CanMove() || bAttacking) return;
	
	ACharacter::StopJumping();
}

void AMain::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::VariationCoin(int32 Amount)
{
	Coins += Amount;
}

void AMain::Die()
{
	if (MS == EMovementStatus::EMS_Dead) return;

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && CombatMontage)
	{
		animInstance->Montage_Play(CombatMontage, 2.0f);
		animInstance->Montage_JumpToSection(FName("Death"),CombatMontage);
	}
	UGameplayStatics::PlaySound2D(this, DeathSound, GM->EffectVolume);
	if (MainPlayerController)
		MainPlayerController->DisplayDeadUI();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	SetMovementStatus(EMovementStatus::EMS_Dead);
}

void AMain::TickStamina(float DeltaTime)
{
	float deltaStamina = StaminaDrainRate * DeltaTime;
	float& currentStamina = StatManager->CurrentStamina;
	const float maxStamina = StatManager->MaxStamina;
	switch (ESS)
	{
	case EStaminaStatus::ESS_Normal:
		bCanSprint = true;
		if (MS == EMovementStatus::EMS_Sprinting)
		{
			if (GetVelocity().Size() >= 0.1f)
				currentStamina -= deltaStamina*2;
			else
			{
				currentStamina += deltaStamina;
				if (currentStamina >= maxStamina)
					currentStamina = maxStamina;
			}

			if (currentStamina <= MinSprintStamina)
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
		}
		else
		{
			currentStamina += deltaStamina;
			if (currentStamina >= maxStamina)
				currentStamina = maxStamina;
		}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if (MS == EMovementStatus::EMS_Sprinting)
		{
			if (GetVelocity().Size() >= 0.1f)
				currentStamina -= deltaStamina;
			else
			{
				currentStamina += deltaStamina;
				if (currentStamina >= MinSprintStamina)
					SetStaminaStatus(EStaminaStatus::ESS_Normal);
			}

			if (currentStamina <= 0.f)
			{
				bCanSprint = false;
				SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
				SetMovementStatus(EMovementStatus::EMS_Exhausted);
				currentStamina = 0.f;
			}
		}
		else
		{
			currentStamina += deltaStamina;
			if(currentStamina >= MinSprintStamina)
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
		}
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		currentStamina += deltaStamina;
		if (currentStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	
	default:
		break;
	}
}

void AMain::SetMovementStatus(EMovementStatus Input)
{
	MS = Input;

	if (MS == EMovementStatus::EMS_Sprinting)
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	else if (MS == EMovementStatus::EMS_Normal)
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = 0.f;

}

void AMain::SetSprinting()
{
	if(bCanSprint && MS != EMovementStatus::EMS_Exhausted && MS != EMovementStatus::EMS_Dead)
	SetMovementStatus(EMovementStatus::EMS_Sprinting);
}

void AMain::SetRunning()
{
	if(MS != EMovementStatus::EMS_Exhausted && MS != EMovementStatus::EMS_Dead)
	SetMovementStatus(EMovementStatus::EMS_Normal);
}
void AMain::MainApplyDamage(AEnemy* _Enemy , TSubclassOf<UDamageType> _DamageTypeClass)
{
	if (_DamageTypeClass)
	{
		float damage = StatManager->Damage;
		switch(ESD)
		{
		case ESkillDamage::ESD_Normal:
			damage = damage * 1.0f;
			break;
		case ESkillDamage::ESD_Slash:
			damage = damage * 1.5f;
			break;
		default:
			break;
		}
		UGameplayStatics::ApplyDamage(_Enemy, damage, WeaponInstigator, this, _DamageTypeClass);
	}
}
void AMain::ApplyMagicDamage(AEnemy * _Enemy, TSubclassOf<UDamageType> _DamageTypeClass,float _Damage)
{
	if (_DamageTypeClass)
	{
		UGameplayStatics::ApplyDamage(_Enemy, _Damage, WeaponInstigator, this, _DamageTypeClass);
	}
}
void AMain::PressKeyF()
{
	if (ItemBox== nullptr || !CanMove()) return;

	if (MainPlayerController)
	{
		if (MainPlayerController->bOpenItemBox)
		{
			for (AItem* item : ItemBox->Items)
			{
				InventoryComp->AddToInventory(item);
			}
			ItemBox->Items.Empty();
			DelOpenItemBox.Broadcast(ItemBox->Items);
			ItemBox->DestroyCheck();
		}
		else
		{
			MainPlayerController->RemovePressF();
			OpenItemBox();
		}
	}
}

void AMain::PressKeyG()
{
	CastingSpell(1);
}
void AMain::PressKeyH()
{
	CastingSpell(2);
}
FRotator AMain::GetLookAtRotationYaw(FVector TargetLocation)
{
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	FRotator lookAtRotationYaw(0.f, lookAtRotation.Yaw, 0.f);
	
	return lookAtRotationYaw;
}

void AMain::Attack()
{
	if (!EquippedWeapon || bAttacking || !CanMove() || bDash) return;

	if (!IsValid(CombatTarget)) CombatTarget = nullptr;

	SetInterpToEnemy(true);
	bAttacking = true;
	bComboCheck = false;
	bCanComboAttack = false;
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && CombatMontage)
	{
		animInstance->Montage_Play(CombatMontage,2.0f);
		animInstance->Montage_JumpToSection(FName(*FString::Printf(TEXT("Attack_%d"),CurrentCombo)), CombatMontage);
	}
	UGameplayStatics::PlaySound2D(this, AttackSound, GM->EffectVolume);
}

void AMain::ComboAttack()
{
	if (!bAttacking || !bComboCheck) return;

	//UE_LOG(LogTemp, Warning, TEXT("ComboAttack func"));
	bCanComboAttack = true;


}

void AMain::ComboCheck()
{
	bComboCheck = true;
}

void AMain::AttackEnd()
{

	if (!bCanComboAttack || CurrentCombo == MaxCombo)
	{
		bAttacking = false;
		SetInterpToEnemy(false);
		bComboCheck = false;
		bCanComboAttack = false;
		CurrentCombo = 1;
		return;
	}

	CurrentCombo++;
	bAttacking = false;
	Attack();
	return;

}

void AMain::DashEnd()
{
	bCanComboAttack = false;
	if (MS == EMovementStatus::EMS_Sprinting)
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	else if (MS == EMovementStatus::EMS_Normal)
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = 0.f;


	bCanDash = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bDash = false;

	AttackEnd();

}

void AMain::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;

}

void AMain::DashCheck1()
{
	bDashCheck = true;
	GetWorldTimerManager().SetTimer(DashHandle, this, &AMain::DashCheck2, 0.5f);
}

void AMain::DashCheck2()
{
	bDashCheck = false;
}

void AMain::Dash()
{
	if (StatManager->CurrentStamina < 50 || !bCanDash || !CanMove() || (!bIsFMoved && !bIsRMoved) || !bDashCheck || bAttacking)
	{
		return;
	}

	bCanDash = false;
	StatManager->CurrentStamina -= 50;
	bDash = true;
	SetInterpToEnemy(false);
	if (EquippedWeapon)
		EquippedWeapon->DeactivateCollision();

	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	const FVector Direction = GetActorForwardVector();//FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	DashLocation = GetActorLocation() + (Direction * 500.f);

	UGameplayStatics::PlaySound2D(this, DashSound, GM->EffectVolume);
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && CombatMontage)
	{
		animInstance->Montage_Play(CombatMontage, 1.0f);
		animInstance->Montage_JumpToSection(FName(TEXT("Dash")), CombatMontage);
	}
}

void AMain::CastingSpell(int32 _SpellNum)
{
	switch (_SpellNum)
	{
	case 1: // slash attack 스킬-> 1번 
		Skill_SlashAttack();
		break;
	case 2:// Fireball 스킬-> 2번 
		Skill_Fireball();
		break;
	default:
		break;
	}
}

void AMain::Skill_SlashAttack()
{
	if (!EquippedWeapon || bAttacking || !CanMove() || bDash) return;

	if (!IsValid(CombatTarget)) CombatTarget = nullptr;
	if (StatManager->CurrentStamina < 90.f) return;
	SetInterpToEnemy(true);
	bAttacking = true;
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && SkillMontage)
	{
		animInstance->Montage_Play(SkillMontage, 2.0f);
		animInstance->Montage_JumpToSection(FName(TEXT("SlashAttack")), SkillMontage);
	}
	StatManager->CurrentStamina -= 90.f;
}
void AMain::Skill_Fireball()
{
	if (bAttacking || !CanMove() || bDash) return;

	if (!IsValid(CombatTarget)) CombatTarget = nullptr;

	if (StatManager->CurrentStamina < 50.f) return;

	bAttacking = true;
	const FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation = GetActorRotation();
	YawRotation.Yaw = Rotation.Yaw;
	SetActorRotation(YawRotation);
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (animInstance && SkillMontage)
	{
		animInstance->Montage_Play(SkillMontage, 1.7f);
		animInstance->Montage_JumpToSection(FName(TEXT("FireBall")), SkillMontage);
	}
	StatManager->CurrentStamina -= 50.f;
}
void AMain::SpawnFireBall()
{
	if (FireBall)
	{
		UWorld* world = GetWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator = GetActorRotation();
		FVector  SpawnLocation = GetMesh()->GetSocketLocation("LeftHandMiddle3");

		ASkill_FireBallObject* spawnActor = Cast<ASkill_FireBallObject>(world->SpawnActor<AActor>(FireBall, SpawnLocation, rotator, SpawnParams));
		if (spawnActor)
		{
			spawnActor->SetTarget(CombatTarget);
			spawnActor->SetOwnerCharacter(this);
		}
	}
}
void AMain::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}

void AMain::SimpleTakeDamage(float DamageAmount)
{
	StatManager->CurrentHealth -= DamageAmount;
	if (DamageAmount > 0)
		UGameplayStatics::PlaySound2D(this, HitSound, GM->EffectVolume);

	if (StatManager->CurrentHealth <= 0) {
		Die();
	}
}

float AMain::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float& currentHealth = StatManager->CurrentHealth;

	if (DamageAmount > 0)
	{
		float Damage = DamageAmount - StatManager->DEF;
		if (Damage < 1) Damage = 1;

		currentHealth -= Damage;
		if (bDash)
		{
			currentHealth += Damage;
			return DamageAmount;
		}
		if (currentHealth <= 0) {
			Die();
			AEnemy* enemy = Cast<AEnemy>(DamageCauser);
			if (enemy)
			{
				enemy->bHasValidTarget = false;
			}
			return DamageAmount;
		}

		if (DamageAmount > 0)
			UGameplayStatics::PlaySound2D(this, HitSound, GM->EffectVolume);

	}
	else if (DamageAmount < 0)
	{
		currentHealth -= DamageAmount;

		if (currentHealth > StatManager->MaxHealth)
			currentHealth = StatManager->MaxHealth;

		UGameplayStatics::PlaySound2D(this, HealSound, GM->EffectVolume);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealParticles, GetActorLocation(), FRotator(0.f), true);
		UGameplayStatics::SpawnEmitterAttached(HealParticles, GetMesh(), "ParticleSocket");
	}

	return DamageAmount;
}

void AMain::SwitchLevel(FName LevelName)
{
	UWorld* world = GetWorld();

	if (world)
	{
		FString currentLevel = world->GetMapName();
		FName currentLevelName(*currentLevel);
		if (currentLevelName != LevelName)
		{
			SaveGame();
			UGameplayStatics::OpenLevel(this, LevelName, false);
		}
	}
}
void AMain::RestartLevel()
{
	if (MS != EMovementStatus::EMS_Dead) return;

	if(MainPlayerController)
		MainPlayerController->RemoveDeadUI();
	UWorld* world = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("restart func1"));
	if (world)
	{
		UMySaveGame* loadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		loadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(loadGameInstance->PlayerName, loadGameInstance->UserIdx));
		if (loadGameInstance != nullptr)
		{
			if (loadGameInstance->LevelName == FName(world->GetName()))
			{
				loadGameInstance->bIsSaved = true;
				UGameplayStatics::SaveGameToSlot(loadGameInstance, loadGameInstance->PlayerName, loadGameInstance->UserIdx);
			}
		}

		UGameplayStatics::OpenLevel(this, FName(world->GetName()), false);
	}
}

void AMain::UseQuickSlotItem(int32 _Idx)
{
	TArray<class APotion*> quickSlot = InventoryComp->PotionActionBar;

	if (_Idx < 0 || _Idx >quickSlot.Num()) return;

	APotion* potion = quickSlot[_Idx];
	if (potion)
	{
		potion->UseItem(this);
		InventoryComp->DelUpdatePotionActionBar.Broadcast(InventoryComp->PotionActionBar);
		InventoryComp->DelUpdateInventory.Broadcast(InventoryComp->Inventory);
	}
}

void AMain::SaveGame()
{
	if (MS == EMovementStatus::EMS_Dead) return;

	UMySaveGame* saveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	saveGameInstance->CharacterStats.Health = StatManager->CurrentHealth;
	saveGameInstance->CharacterStats.MaxHealth = StatManager->MaxHealth;
	saveGameInstance->CharacterStats.Stamina = StatManager->CurrentStamina;
	saveGameInstance->CharacterStats.MaxStamina = StatManager->MaxStamina;
	saveGameInstance->CharacterStats.coins = Coins;
	saveGameInstance->CharacterStats.Level = StatManager->Level;
	saveGameInstance->CharacterStats.Exp = StatManager->Exp;
	saveGameInstance->LevelName = FName(GetWorld()->GetName());

	if (EquippedWeapon)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(EquippedWeapon->Name,1);
	}
	if (ArmorHead)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(ArmorHead->Name,2);
	}
	if (ArmorShoes)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(ArmorShoes->Name,2);
	}
	if (ArmorChest)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(ArmorChest->Name,2);
	}
	if (ArmorPant)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(ArmorPant->Name,2);
	}
	if (ArmorShield)
	{
		saveGameInstance->CharacterStats.EqippedItemMap.Add(ArmorShield->Name,2);
	}

	for (AItem* item : InventoryComp->Inventory)
	{
		if (item)
		{
			//UE_LOG(LogTemp, Warning, TEXT("item name :: %s"), *(item->Name));
			APotion* potion = Cast<APotion>(item);
			if (potion)
			{
				for (int i = 0; i < potion->Amount; i++)
				{
					saveGameInstance->CharacterStats.Inventory.Add(item->Name);
				}
				saveGameInstance->CharacterStats.QuickIdx = InventoryComp->PotionActionBar.Find(potion);
			}
			else
				saveGameInstance->CharacterStats.Inventory.Add(item->Name);
		}
		//saveGameInstance->CharacterStats.Inventory.Add(item->Name);
	}

	saveGameInstance->CharacterStats.Location = GetActorLocation();
	saveGameInstance->CharacterStats.Rotation = GetActorRotation();
	saveGameInstance->bIsSaved = true;
	UE_LOG(LogTemp, Warning, TEXT("SaveGame"));
	UGameplayStatics::SaveGameToSlot(saveGameInstance, saveGameInstance->PlayerName, saveGameInstance->UserIdx);

}

void AMain::LoadGame(bool SetPosition)
{
	UMySaveGame* loadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	loadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(loadGameInstance->PlayerName, loadGameInstance->UserIdx));
	if (loadGameInstance == nullptr) return;
	if (!loadGameInstance->bIsSaved) return;

	StatManager->CurrentHealth = loadGameInstance->CharacterStats.Health;
	StatManager->MaxHealth = loadGameInstance->CharacterStats.MaxHealth;
	StatManager->CurrentStamina = loadGameInstance->CharacterStats.Stamina;
	StatManager->MaxStamina = loadGameInstance->CharacterStats.MaxStamina;
	for (int i = 1; i < loadGameInstance->CharacterStats.Level; i++)
	{
		StatManager->LevelUp();
	}

	StatManager->Exp = (loadGameInstance->CharacterStats.Exp);

	if (WeaponStorage)
	{
		AItemStorage* storage = GetWorld()->SpawnActor<AItemStorage>(WeaponStorage);
		if (storage)
		{
			//FString weaponName;
			TArray<FString> InvenItems = loadGameInstance->CharacterStats.Inventory;
			//if (weapons->WeaponMap.Contains(weaponName))
			//{
			//	AWeapon* weaponToEquip = GetWorld()->SpawnActor<AWeapon>(weapons->WeaponMap[weaponName]);
			//	weaponToEquip->Equip(this);
			//}
			int invenIdx = 0;
			for (FString itemName : InvenItems)
			{
				if (storage->ItemMap.Contains(itemName))
				{
					//UE_LOG(LogTemp, Warning, TEXT("load item name :: %s"),*itemName);
					AItem* invenItem = GetWorld()->SpawnActor<AItem>(storage->ItemMap[itemName]);
					AddToItem(invenItem);
					//장착아이템에 들어있는경우
					if (loadGameInstance->CharacterStats.EqippedItemMap.Contains(itemName))
					{
						if (loadGameInstance->CharacterStats.EqippedItemMap[itemName] == 1)
						{
							AWeapon* equipWeapon = Cast<AWeapon>(invenItem);
							equipWeapon->UseItem(this);
						}
						else
						{
							AArmor* equipArmor = Cast<AArmor>(invenItem);
							equipArmor->UseItem(this);
						}
					}
					//아닌 경우 -> 포션(이 프로젝트에선)
					else
					{
						if (loadGameInstance->CharacterStats.QuickIdx != INDEX_NONE)
						{
							InventoryComp->AddToQuickSlot(loadGameInstance->CharacterStats.QuickIdx, invenIdx);
						}
					}
					invenIdx++;
				}
			}
		}
	}

	if (SetPosition)
	{
		SetActorLocation(loadGameInstance->CharacterStats.Location);
		SetActorRotation(loadGameInstance->CharacterStats.Rotation);
	}

	SetMovementStatus(EMovementStatus::EMS_Normal);
	GetMesh()->bPauseAnims = false;
	GetMesh()->bNoSkeletonUpdate = false;
	loadGameInstance->bIsSaved = false;
	UGameplayStatics::SaveGameToSlot(loadGameInstance, loadGameInstance->PlayerName, loadGameInstance->UserIdx);
	UE_LOG(LogTemp, Warning, TEXT("LoadGame"));
}


void AMain::ESCDown()
{
	if (MainPlayerController)
	{
		if (MainPlayerController->bOpenItemBox || MainPlayerController->bInvetoryVisible)
		{
			MainPlayerController->RemoveInventory();
			MainPlayerController->RemoveItemBox();
			return;
		}

		bool worldPaused = MainPlayerController->TogglePauseMenu();
		//if (worldPaused == false)
		//	LoadGame(true);

		UGameplayStatics::SetGamePaused(GetWorld(), worldPaused);
			
	}
}


bool AMain::CanMove()
{
	if (MainPlayerController)
	{
		if ((Controller == nullptr) || MS == EMovementStatus::EMS_Exhausted || MS == EMovementStatus::EMS_Dead || MainPlayerController->bPauseMenuVisible)
			return false;
	}

	return true;

}

void AMain::OpenItemBox()
{
	if (!ItemBox) return;

	DelOpenItemBox.Broadcast(ItemBox->Items);
	MainPlayerController->DisplayItemBox();
}

void AMain::AddToItem(AItem * _Item)
{
	if (InventoryComp)
		InventoryComp->AddToInventory(_Item);
}


void AMain::DeleteToItem(AItem * _Item)
{
	int32 idx = InventoryComp->DeleteToInventory(_Item);
}


void AMain::EquipWeapon(AItem * Item)
{
	if (!Item) return;

	AWeapon* weapon = Cast<AWeapon>(Item);
	if (weapon)
	{
		weapon->Equip(this);
		InventoryComp->EquipWeapon1(weapon);
	}
}
void AMain::UnEquipWeapon(AItem* _Item)
{
	if (!_Item || EquippedWeapon == nullptr) return;

	AWeapon* weapon = Cast<AWeapon>(_Item);
	if (weapon)
	{
		weapon->UnEquip(this);
		InventoryComp->UnEquipWeapon(weapon);
	}
}

void AMain::EquipArmor(AItem * Item)
{
	if (!Item) return;

	AArmor* armor = Cast<AArmor>(Item);
	if (armor)
	{
		switch (armor->EAT)
		{
		case EArmorType::EAT_Head:
			InventoryComp->EquipHead(armor);
			ArmorHead = armor;
			break;
		case EArmorType::EAT_Chest:
			InventoryComp->EquipChest(armor);
			ArmorChest = armor;
			break;
		case EArmorType::EAT_Pant:
			InventoryComp->EquipPant(armor);
			ArmorPant = armor;
			break;
		case EArmorType::EAT_Shoes:
			InventoryComp->EquipShoes(armor);
			ArmorShoes = armor;
			break;
		case EArmorType::EAT_Shield:
			InventoryComp->EquipShield(armor);
			ArmorShield = armor;
			break;
		default:
			return;
		}
		armor->Equip(this);
	}
}

void AMain::UnEquipArmor(AItem * _Item)
{
	if (!_Item) return;

	AArmor* armor = Cast<AArmor>(_Item);
	if (armor)
	{
		switch (armor->EAT)
		{
		case EArmorType::EAT_Head:
			InventoryComp->UnEquipHead(armor);
			ArmorHead = nullptr;
			break;
		case EArmorType::EAT_Chest:
			InventoryComp->UnEquipChest(armor);
			ArmorChest = nullptr;
			break;
		case EArmorType::EAT_Pant:
			InventoryComp->UnEquipPant(armor);
			ArmorPant = nullptr;
			break;
		case EArmorType::EAT_Shoes:
			InventoryComp->UnEquipShoes(armor);
			ArmorShoes = nullptr;
			break;
		case EArmorType::EAT_Shield:
			InventoryComp->UnEquipShield(armor);
			ArmorShield = nullptr;
			break;
		default:
			return;
		}
		armor->UnEquip(this);
	}
}

AArmor* AMain::GetArmor(EArmorType ArmorType)
{
	switch (ArmorType)
	{
	case EArmorType::EAT_Head:
		return ArmorHead;
	case EArmorType::EAT_Chest:
		return ArmorChest;
	case EArmorType::EAT_Pant:
		return ArmorPant;
	case EArmorType::EAT_Shoes:
		return ArmorShoes;
	case EArmorType::EAT_Shield:
		return ArmorShield;
	default:
		return nullptr;
	}
}

void AMain::OpenInventory()
{
	if (!MainPlayerController->bInvetoryVisible)
	{
		MainPlayerController->DisplayInventory();
	}
	else
		MainPlayerController->RemoveInventory();
}

void AMain::ShowHelpString(FString Text)
{
	if (!MainPlayerController) return;

	HelpText = Text;
	if (Text == TEXT(""))
	{
		MainPlayerController->RemoveHelpMessage();
	}
	else
	{
		MainPlayerController->DisplayHelpMessage();
		GetWorldTimerManager().ClearTimer(TextHandle);
		TextDel = FTimerDelegate::CreateUObject(this, &AMain::ShowHelpString,FString(TEXT("")));
		GetWorldTimerManager().SetTimer(TextHandle, TextDel, 3.0, false);
	}
}

void AMain::SetItemBox(AItemBox * Target)
{
	if (Target != nullptr)
	{
		if (MainPlayerController)
		{
			MainPlayerController->DisplayPressF();
		}
	}
	else
	{
		if (MainPlayerController)
		{
			MainPlayerController->RemovePressF();
			MainPlayerController->RemoveItemBox();
		}
	}
	ItemBox = Target;
}

