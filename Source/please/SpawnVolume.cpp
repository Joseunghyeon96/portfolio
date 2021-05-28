// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "AIController.h"
#include "Enemy/Enemy.h"
#include "MyCharacter/Main.h"
#include "Boss_ForgeKing/Boss_ForgeKing.h"
#include "Boss_ForgeKing/ForgeKingController.h"

#include "MyPawns/Critter.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpwaningBox"));
	SpawnPointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPointBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (Actor_1)
		SpawnArray.Add(Actor_1);

	if (Actor_2)
		SpawnArray.Add(Actor_2);

	if (Actor_3)
		SpawnArray.Add(Actor_3);

	if (Actor_4)
		SpawnArray.Add(Actor_4);

	SpawningBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawnVolume::SpawningBoxOnOverlapBegin);
	SpawningBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	SpawnPointBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()
{
	FVector point = SpawnPointBox->GetComponentLocation();

	return point;
}

void ASpawnVolume::SpawningBoxOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);
		if (main) {
			UE_LOG(LogTemp, Warning, TEXT("Spawn Overlap"));
			SpawnOurActor(GetSpawnActor(), GetSpawnPoint());
			SpawningBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			
		}
	}
}

TSubclassOf<AActor> ASpawnVolume::GetSpawnActor()
{
	if (SpawnArray.Num() > 0)
	{
		int32 selection = FMath::RandRange(0, SpawnArray.Num() - 1);
		UE_LOG(LogTemp, Warning, TEXT("selection : %d"),selection);

		return SpawnArray[selection];
	}
	return nullptr;
}

void ASpawnVolume::SpawnOurActor_Implementation(UClass* ToSpawn, const FVector & Location)
{
	if (!ToSpawn)return;

	UWorld* world = GetWorld();
	if (!world) return;

	FActorSpawnParameters spawnParams;
	ABoss_ForgeKing* actor = world->SpawnActor<ABoss_ForgeKing>(ToSpawn, Location, FRotator(0.f), spawnParams);
	UE_LOG(LogTemp, Warning, TEXT("Boss Spawn"));
	ABoss_ForgeKing* enemy = Cast<ABoss_ForgeKing>(actor);
	if (enemy)
	{
		enemy->SpawnDefaultController();
	}

}

