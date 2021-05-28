// Copyright Epic Games, Inc. All Rights Reserved.


#include "pleaseGameModeBase.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"

ApleaseGameModeBase::ApleaseGameModeBase()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
	EffectVolume = 1.0f;
	BGMVolume = 1.0f;
}
void ApleaseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainMusicCue)
	{
		AudioComponent->SetSound(MainMusicCue);
		AudioComponent->Play();
	}
}

void ApleaseGameModeBase::SetEffectVolume(float _input)
{
	float volume = FMath::Clamp(_input, 0.f, 1.f);
	EffectVolume = volume;
}


void ApleaseGameModeBase::SetBGMVolume(float _input)
{

	float volume = FMath::Clamp(_input,0.f, 1.f);
	BGMVolume = volume;
	AudioComponent->SetVolumeMultiplier(BGMVolume);
}