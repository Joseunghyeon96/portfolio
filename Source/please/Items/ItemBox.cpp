// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../MyCharacter/Main.h"
#include "Item.h"
#include "../MyCharacter/Weapon.h"

//
//#include "Kismet/GameplayStatics.h"
//#include "Sound/SoundCue.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	RootComponent = Trigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticlesComponent"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::TriggerOnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AItemBox::TriggerOnOverlapEnd);
	
	if (Items.Num() == 0)
		Destroy();
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::TriggerOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		if (main) {
			if (main->ItemBox == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("overlap"));
				main->SetItemBox(this);
				MainCharcter = main;
				FActorSpawnParameters SpawnInfo;

				AWeapon* weaponBase = GetWorld()->SpawnActor<AWeapon>(Weapon, SpawnInfo);
				AItem* item = Cast<AItem>(weaponBase);
				if (item)
				{
					Items.Add(item);
					Weapon = nullptr;
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("item null"));
			}
		}
	}
}

void AItemBox::TriggerOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		if (main) {
			MainCharcter = nullptr;
			if (main->ItemBox == this)
			{
				UE_LOG(LogTemp, Warning, TEXT("overlap end"));
				main->SetItemBox(nullptr);
			}
		}
	}
}

void AItemBox::DestroyCheck()
{
	if (Items.Num() == 0)
	{
		GetWorldTimerManager().SetTimer(DestoryHandle, this, &AItemBox::MyDestroy, 5.0f);
	}
}

void AItemBox::MyDestroy()
{
	if (MainCharcter)
	{
		if (MainCharcter->ItemBox == this)
			MainCharcter->SetItemBox(nullptr);
	}
	Destroy();
}