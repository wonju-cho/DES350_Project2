// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "ItemInteractive.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AItemInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AActor> itemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bItemCollected;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnItemCollected();
	

//////////// ABasicInteractive override methods //////////////////
protected:

	void OnPlayerBeginOverlap() override;

	void OnPlayerEndOverlap() override;

//////////// ABasicInteractive override methods //////////////////

//////////// INTERFACE IInteractable //////////////////
public:

	FName GetName() override;

	// Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();

	//Actual implementation of the Interact event
	void OnInteract_Implementation();

	FName GetQuestID() override;

	//////////// INTERFACE IInteractable //////////////////

};
