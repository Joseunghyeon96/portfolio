// Fill out your copyright notice in the Description page of Project Settings.


#include "HelpMessage.h"
#include "MyCharacter/Main.h"
#include "Components/BoxComponent.h"

// Sets default values
AHelpMessage::AHelpMessage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	RootComponent = Trigger;
}

// Called when the game starts or when spawned
void AHelpMessage::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHelpMessage::TriggerOnOverlapBegin);
}

// Called every frame
void AHelpMessage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelpMessage::TriggerOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		if (main) {
			main->ShowHelpString(Message);
			Message = "";
		}
	}
}

