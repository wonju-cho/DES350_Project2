// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item System")
	class UItemData* itemDataBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest System")
	class UQuestData* questDataBase;

public:
	int32 GetQuestNum();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item System")
	FItem FindItem(FName itemID, bool& success);

	FItem FindItem_Implementation(FName itemID, bool& success);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	FQuest FindQuest(FName questID, bool& success);

	FQuest FindQuest_Implementation(FName questID, bool& success);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void CallEndGame();

};




