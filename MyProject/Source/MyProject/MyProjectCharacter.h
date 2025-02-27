// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "Definitions.h"
#include "MyProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	void Action();

	void OnActorEnter(AActor* interactiveActor);

	void OnLeaveActor();

protected:

	TArray<FQuestItem> questList;
	
	AActor* currentInteractiveActor;

	IInteractable* currentInteractive;
	
public:
	bool FindQuest(FName questID, FQuestItem& quest);

	void AcceptQuest(FName questID);

	void MarkQuestCompleted(FName questID);

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowQuestInfo(FQuest Quest);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowQuestCompleted(const FText& message);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowUpdatedQuestList(const TArray<FText>& questTextList);

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnShowUI(FName characterName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnHideUI();
	
protected:
	void UpdateAndShowQuestList();

	//inventory
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItem> equipmentInventory;

	//maximum slots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 totalEquipmentSlots = 6;

public:

	void AddItem(FName ItemID);

	void RemoveItem(FName ItemID);

	bool HasFreeInventorySlots();

	bool HasItem(FName ItemID);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnRefreshInventory();
	
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void BeginPlay() override;

	int32 questNum;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//f1
	UFUNCTION(BlueprintCallable)
	void CheatGrape();

	//f2
	UFUNCTION(BlueprintCallable)
	void CheatMeat();

	//f3
	UFUNCTION(BlueprintCallable)
	void CheatSomething();

	//f4
	UFUNCTION(BlueprintCallable)
	void CheatHay();
	

	
};

