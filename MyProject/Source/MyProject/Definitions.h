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
	FName characterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName questID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText message;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText completeMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName itemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TSoftObjectPtr<UTexture2D> iconReference;

	bool isCompleted;
};

UCLASS(BlueprintType)
class UQuestData: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TArray<FQuest> questData;
		
};

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName itemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr<UTexture2D> iconReference;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr<UStaticMesh> meshReference;

	
};

UCLASS(BlueprintType)
class UItemData: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TArray<FItem> itemData;
		
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
