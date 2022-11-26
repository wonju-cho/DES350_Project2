// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInteractive.h"

#include "MyProjectCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasicInteractive::ABasicInteractive()
{
	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = rootScene;

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	trigger->SetupAttachment(RootComponent);

	trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasicInteractive::BeginOverlap);
	trigger->OnComponentEndOverlap.AddUniqueDynamic(this, &ABasicInteractive::EndOverlap); 
	
	PrimaryActorTick.bCanEverTick = false;

}

void ABasicInteractive::BeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playerCharacter = Cast<AMyProjectCharacter>(OtherActor);

	if(playerCharacter != nullptr)
	{
		playerCharacter->OnActorEnter(this);

		OnPlayerBeginOverlap();
	}
}

void ABasicInteractive::OnPlayerBeginOverlap ()
{
}

void ABasicInteractive::EndOverlap (UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(playerCharacter != nullptr)
	{
		playerCharacter->OnLeaveActor();

		OnPlayerEndOverlap();
	}
}

void ABasicInteractive::OnPlayerEndOverlap ()
{
}

