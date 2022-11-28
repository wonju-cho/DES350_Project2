// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"

AChest::AChest ()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChest::OnPlayerBeginOverlap ()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->OnShowUI(interactiveName);
	}
}

void AChest::OnPlayerEndOverlap ()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->OnHideUI();
	}}

FName AChest::GetName ()
{
	return interactiveName;
}

void AChest::OnInteract_Implementation ()
{
	AMyProjectGameMode* gameMode = Cast<AMyProjectGameMode>(GetWorld()->GetAuthGameMode());

	if(gameMode == nullptr)
		return;

	if(!questActivated)
		return;

	bool success = false;

	FQuest quest = gameMode->FindQuest(QuestID, success);

	if(!success)
		return;

	bool bQuestAccepted = false;

	FQuestItem questInfo;

	bQuestAccepted = playerCharacter -> FindQuest(QuestID, questInfo);

	if(!bQuestAccepted)
	{
		playerCharacter->OnShowQuestInfo(quest);
		playerCharacter->AcceptQuest(QuestID);
	}
	else
	{
		//if the player has quest then check the inventory and remove that item
		if(!questInfo.IsCompleted)
		{
			if(playerCharacter->HasItem(quest.ItemID))
			{
				playerCharacter->RemoveItem(quest.ItemID);
				playerCharacter->MarkQuestCompleted(QuestID);

				playerCharacter->OnShowQuestCompleted(quest.CompleteMessage);
				questActivated = false;
				quest.isQuestCompleted = true;
				this->Destroy();
			}
			else
			{
				playerCharacter->OnShowQuestInfo(quest);
			}
		}
		else
		{
			playerCharacter->OnShowQuestInfo(quest);
		}

	}
}

FName AChest::GetQuestID ()
{
	return QuestID;
}
