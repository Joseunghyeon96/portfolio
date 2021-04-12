// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Main.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "../Enemy.h"

#define FloatToString(input) (FString::SanitizeFloat(input))

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	CombatCollision->SetupAttachment(GetRootComponent());
	WeaponState = EWeaponState::EWS_Pickup;
	Type = EItemType::ItemType_Equip;
}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapEnd);

	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TypeTooltip = Korean(장비 아이템);
	ItemTooltip += "Damage : " + FloatToString(Damage) + "\n" + WeaponTooltip;
}
void AWeapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (WeaponState == EWeaponState::EWS_Pickup && OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);
		if (main)
		{
			main->SetActiveOverlappingItem(this);
		}
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);
		if (main)
		{
			main->SetActiveOverlappingItem(nullptr);
		}
	}
}

void AWeapon::CombatOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OwnerCharacter == nullptr) return;

	if (OtherActor)
	{
		AEnemy* enemy = Cast<AEnemy>(OtherActor);
		if (enemy)
		{
			if (enemy->HitParticles)
			{
				//const USkeletalMeshSocket* weaponSocket = SkeletalMesh->GetSocketByName("WeaponSocket");
				//if (weaponSocket)
				//{
					//FVector socketLocation = weaponSocket->GetSocketLocation(SkeletalMesh);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), enemy->HitParticles, OtherComp->GetComponentLocation(), FRotator(0.f), false);
				//}
			}
			if (enemy->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, enemy->HitSound);
			}
			if (DamageTypeClass)
			{
				OwnerCharacter->MainApplyDamage(enemy, DamageTypeClass);
			}
		}
	}
}

void AWeapon::CombatOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}

void AWeapon::Equip(AMain * Character)
{
	if (!Character) return;


	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetSimulatePhysics(false);
	OwnerCharacter = Character;
	WeaponInstigator = Character->GetController();

	const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");
	if (RightHandSocket)
	{
		RightHandSocket->AttachActor(this, Character->GetMesh());
		Character->SetEquippedWeapon(this);
		Character->SetActiveOverlappingItem(nullptr);
		if (OnEquipSound)
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);
		}
	}
	

}

void AWeapon::UseItem(AMain * _Main)
{
	if (_Main == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("weapon useitem func"));
	Super::UseItem(_Main);
	_Main->EquipWeapon(this);
}

void AWeapon::UnEquip(AMain * Character)
{
	if (!Character || OwnerCharacter != Character) return;

	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SkeletalMesh->SetSimulatePhysics(true);
	OwnerCharacter = nullptr;
	WeaponInstigator = nullptr;

	const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");
	if (RightHandSocket)
	{
		Character->SetEquippedWeapon(nullptr);
		this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Un Equip Func"));
}

void AWeapon::ActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UGameplayStatics::PlaySound2D(this, SwingSound);
}

void AWeapon::DeactivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

