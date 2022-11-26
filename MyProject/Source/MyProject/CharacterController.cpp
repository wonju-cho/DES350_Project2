// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProjectCharacter.h"
#include "CharacterController.h"

void ACharacterController::BeginPlay ()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	playerCharacter = Cast<AMyProjectCharacter>(GetPawn());
}

void ACharacterController::SetupInputComponent ()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterController::Action).bConsumeInput = false;

}

void ACharacterController::Action ()
{
	if(playerCharacter != nullptr)
	{
		playerCharacter->Action();
	}
}
