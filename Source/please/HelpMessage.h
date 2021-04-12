// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HelpMessage.generated.h"

UCLASS()
class PLEASE_API AHelpMessage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelpMessage();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Trigger")
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
	FString Message;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void TriggerOnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
