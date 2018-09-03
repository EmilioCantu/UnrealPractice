// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "FPSCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
   meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
   meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
   RootComponent = meshComp;

   sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
   sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   sphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
   sphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
   sphereComp->SetupAttachment(meshComp);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
   PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
   UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
   Super::NotifyActorBeginOverlap(OtherActor);
   PlayEffects();

   AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
   if(MyCharacter)
   {
      MyCharacter->bIsCarryingObjective = true;
      Destroy();
   }
}

