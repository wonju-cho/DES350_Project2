// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Definitions.generated.h"


USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_USTRUCT_BODY()	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName CharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName QuestID;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText Message;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText SortDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText CompleteMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	UTexture2D* ItemQuestTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	bool isQuestCompleted;

	
};


UCLASS(BlueprintType)
class UQuestData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuest> QuestData;	
};

USTRUCT(BlueprintType)
struct FQuestItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	bool IsCompleted;
};


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Player Inventory")
	int32 Quantity;
};



UCLASS(BlueprintType)
class UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TArray<FItem> ItemData;
};


/**
 * 
 */
class MYPROJECT_API Definitions
{
public:
	Definitions();
	~Definitions();
};
