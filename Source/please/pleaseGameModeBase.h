// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "pleaseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLEASE_API ApleaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ApleaseGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	class USoundCue* MainMusicCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
	float BGMVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
	float EffectVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetEffectVolume(float _input);

	UFUNCTION(BlueprintCallable)
	void SetBGMVolume(float _input);
};
