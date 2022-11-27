// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "MyProjectCharacter.h"
#include "MyProjectGameMode.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
ANPC::ANPC()
{

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	trigger->SetupAttachment(RootComponent);

	trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANPC::BeginOverlap);
	trigger->OnComponentEndOverlap.AddUniqueDynamic(this, &ANPC::EndOverlap);
	
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	isQuestActivated = true;
	
	SetActorTickEnabled(true);
}


void ANPC::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(playerCharacter != nullptr)
		return;

	AMyProjectCharacter* otherCharacter = Cast<AMyProjectCharacter>(OtherActor);

	if(otherCharacter != nullptr)
	{
		float dotProduct = FVector::DotProduct(otherCharacter->GetActorForwardVector(), GetActorForwardVector());

		UE_LOG(LogTemp, Warning, TEXT("Dot Product CatCharacter and Player: %f "), dotProduct);
		
		// DotProduct > 0.0f Same direction
		// DotProduct == 0.0f Perpendicular direction
		// DotProduct < 0.0f Opposite direction
		if(dotProduct < 0.0f)
		{
			playerCharacter = otherCharacter;
			
			playerCharacter->OnActorEnter(this);

			playerCharacter->OnShowUI(characterName);

			OnPlayerEnter();
		}
	}

}


void ANPC::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(playerCharacter != nullptr)
	{
		playerCharacter->OnLeaveActor();
		playerCharacter->OnHideUI();
	}
	playerCharacter = nullptr;
}

void ANPC::OnInteract_Implementation ()
{
	AMyProjectGameMode* gameMode = Cast<AMyProjectGameMode>(GetWorld()->GetAuthGameMode());

	if(gameMode == nullptr)
		return;

	if(!isQuestActivated)
		return;

	bool success = false;

	FQuest quest = gameMode->FindQuest(questID, success);

	if(!success)
		return;

	bool bQuestAccepted = false;

	FQuestItem questInfo;

	bQuestAccepted = playerCharacter -> FindQuest(questID, questInfo);

	if(!bQuestAccepted)
	{
		playerCharacter->OnShowQuestInfo(quest);
		playerCharacter->AcceptQuest(questID);
	}
	else
	{
		//if the player has quest then check the inventory and remove that item
		if(!questInfo.IsCompleted)
		{
			if(playerCharacter->HasItem(quest.ItemID))
			{
				playerCharacter->RemoveItem(quest.ItemID);
				playerCharacter->MarkQuestCompleted(questID);

				playerCharacter->OnShowQuestCompleted(quest.CompleteMessage);
				isQuestActivated = false;
			
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

FName ANPC::GetQuestID ()
{
	return questID;
}

FName ANPC::GetName ()
{
	return characterName;
}
