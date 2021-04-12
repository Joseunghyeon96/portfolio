// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_FireBallObject.h"
#include "../Enemy.h"
#include "Main.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ASkill_FireBallObject::ASkill_FireBallObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->InitSphereRadius(300.f);

}

// Called when the game starts or when spawned
void ASkill_FireBallObject::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASkill_FireBallObject::CollisionSphereOnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ASkill_FireBallObject::CollisionSphereOnOverlapEnd);

	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	FTimerDelegate delegate;
	delegate.BindLambda([this] { Destroy(); });
	//Uses different SetTimer overload
	GetWorld()->GetTimerManager().SetTimer(Timer, delegate, 3.0f, false);

	
}

// Called every frame
void ASkill_FireBallObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target)
	{
		FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
		FRotator lookAtRotationYaw(0.f, lookAtRotation.Yaw, 0.f);
		FRotator interpRotation = FMath::RInterpTo(GetActorRotation(), lookAtRotationYaw, DeltaTime, 10.0f);
		SetActorRotation(interpRotation);
	}

	FVector nextLocation = GetActorLocation() + GetActorForwardVector()* Speed;
	SetActorRelativeLocation(nextLocation, true);
}

void ASkill_FireBallObject::CollisionSphereOnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AMain* main = Cast<AMain>(OtherActor);

		// 메인 캐릭터면 충돌체크 X
		if (main== nullptr) {
			AEnemy* enemy = Cast<AEnemy>(OtherActor);
			// 적과 충돌했다면
			if (enemy)
			{
	
			}
			if (HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), FRotator(0.f), false);
			}
			Destroy(this);
			UE_LOG(LogTemp, Warning, TEXT("fireball overlappppppppp!!34"));
		}
	}

}

void ASkill_FireBallObject::CollisionSphereOnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void ASkill_FireBallObject::SetTarget(AEnemy* _Target)
{
	if (_Target != nullptr)
	{
		Target = _Target;
	}
}

