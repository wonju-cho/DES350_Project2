// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{

}

int32 AMyProjectGameMode::GetQuestNum ()
{
	return questDataBase->QuestData.Num();
}

FItem AMyProjectGameMode::FindItem_Implementation (FName itemID, bool& success)
{
	success = false;

	FItem item;
	
	if(itemDataBase == nullptr)
		return item;

	for(int i = 0; i < itemDataBase->ItemData.Num(); i++)
	{
		if(itemDataBase->ItemData[i].ItemID == itemID)
		{
			success = true;
			return itemDataBase->ItemData[i];
		}
	}
	
	return item;
}

FQuest AMyProjectGameMode::FindQuest_Implementation (FName questID, bool& success)
{
	success = false;
	
	FQuest quest;
	if(questDataBase == nullptr)
		return quest;

	for(int i = 0; i < questDataBase->QuestData.Num(); i++)
	{
		if(questDataBase->QuestData[i].QuestID == questID)
		{
			questDataBase->QuestData[i].isQuestCompleted = true;
			success = true;
			return questDataBase->QuestData[i];
		}
	}
	
	return quest;
}