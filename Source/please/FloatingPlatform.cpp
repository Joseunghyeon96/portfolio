// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "MyUtility.h"
#include "TimerManager.h"


// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	StartPoint = FVector(0.f);
	EndPoint = FVector(0.f);

	InterpSpeed = 1.0f;
	InterpTime = 1.f;

	bInterping = false;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	Distance = (EndPoint - StartPoint).Size();
	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bInterping)
	{
		PlatformMove(DeltaTime);
	}
}

void AFloatingPlatform::ToggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingPlatform::PlatformMove(float DeltaTime)
{
	FVector currentLocation = GetActorLocation();
	FVector interp = FMath::VInterpTo(currentLocation, EndPoint, DeltaTime, InterpSpeed);
	SetActorLocation(interp);

	float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
	if (Distance - DistanceTraveled <= 0.1f)
	{
		ToggleInterping();
		GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
		SwapVectors(StartPoint, EndPoint);
	}
}

