// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractive.h"

#include "MyProjectCharacter.h"

void AItemInteractive::BeginPlay ()
{
	Super::BeginPlay();

	bItemCollected = false;
}

void AItemInteractive::OnPlayerBeginOverlap ()
{
	if(playerCharacter != nullptr)
	{
		playerCharacter->OnShowUI(interactiveName);
	}
}

void AItemInteractive::OnPlayerEndOverlap ()
{
	if(playerCharacter != nullptr)
	{
		playerCharacter->OnHideUI();
	}
}

void AItemInteractive::OnInteract_Implementation ()
{
	if(bItemCollected)
		return;

	if(playerCharacter != nullptr)
	{
		if(playerCharacter->HasFreeInventorySlots())
		{
			playerCharacter->AddItem(ItemID);
			
			bItemCollected = true;
			
			OnItemCollected();
		}

	}
}

FName AItemInteractive::GetName ()
{
	return interactiveName;
}

FName AItemInteractive::GetQuestID ()
{
	return QuestID;
}


