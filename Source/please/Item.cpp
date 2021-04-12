﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "MyCharacter/Main.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticlesComponent"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());

	bRotate = false;
	RotationRate = 45.f;

	ItemCode = 1;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator rotation = GetActorRotation();
		rotation.Yaw += DeltaTime * RotationRate;

		SetActorRotation(rotation);
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (!OtherActor) return;

	if (OverlapParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
	}
	if (OverlapSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}

}

void AItem::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (!OverlapParticles) {
		//UE_LOG(LogTemp, Warning, TEXT("Super::Overlap particles null"));
		return;
	}
}

void AItem::UseItem(AMain * _Main)
{
	UE_LOG(LogTemp, Warning, TEXT("item virtual useitem func"));
}

FString AItem::ConvertHexToFString(FString & _InputStr)
{
	FString result;

	int count = _InputStr.Len() / 4;
	for (int i = 0; i < count; i++)
	{
		FString tempFString = _InputStr.Mid(i * 4, 4);
		std::string tempStr(TCHAR_TO_UTF8(*tempFString));
		int strHex = strtoul(tempStr.c_str(), 0, 16);

		result.AppendChar(strHex);
	}
	return result;
}

