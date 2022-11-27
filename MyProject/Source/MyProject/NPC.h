// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class MYPROJECT_API ANPC : public ACharacter, public IInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
	class UBoxComponent* trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC")
	FName characterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC")
	FName questID;

	class AMyProjectCharacter* playerCharacter;

	bool isQuestActivated = false;
	
public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "NPC")
		void OnPlayerEnter();
	
public:
	FName GetName() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();

	//Actual implementation of the Interact
	void OnInteract_Implementation();
	
	FName GetQuestID() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* excitedMontage;
};
