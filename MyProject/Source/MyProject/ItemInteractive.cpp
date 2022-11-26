// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractive.h"

void AItemInteractive::BeginPlay ()
{
	Super::BeginPlay();

	bItemCollected = false;
}

void AItemInteractive::OnPlayerBeginOverlap ()
{
	if(playerCharacter != nullptr)
	{
		//playerCharacter ->OnShowUI(itemName);
	}
}

void AItemInteractive::OnPlayerEndOverlap ()
{
	if(playerCharacter != nullptr)
	{
		//playerCharacter ->OnHideUI();
	}
}

void AItemInteractive::OnInteract_Implementation ()
{
	IInteractable::OnInteract_Implementation();

	if(bItemCollected)
		return;

	if(playerCharacter != nullptr)
	{
		bItemCollected = true;

		OnItemCollected();
	}
}

FName AItemInteractive::GetName ()
{
	return itemName;
}

FName AItemInteractive::GetQuestID ()
{
	return "";
}


