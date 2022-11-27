// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

FItem AMyProjectGameMode::FindItem_Implementation (FName itemID, bool& success)
{
	success = false;

	FItem item;
	if(itemDataBase == nullptr)
		return item;

	for(int i = 0; i < itemDataBase->itemData.Num(); i++)
	{
		if(itemDataBase->itemData[i].itemID == itemID)
		{
			success = true;
			return itemDataBase->itemData[i];
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

	for(int i = 0; i < questDataBase->questData.Num(); i++)
	{
		if(questDataBase->questData[i].questID == questID)
		{
			success = true;
			return questDataBase->questData[i];
		}
	}
	
	return quest;
}
