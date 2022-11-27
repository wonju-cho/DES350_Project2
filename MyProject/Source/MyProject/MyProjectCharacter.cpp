// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyProjectGameMode.h"
#include "Camera/CameraComponent.h"
#include "Chaos/PBDCollisionConstraintsContact.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyProjectCharacter::TouchStopped);

}

void AMyProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AMyProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMyProjectCharacter::BeginPlay ()
{
	Super::BeginPlay();

	OnRefreshInventory();

	questList.Empty();
}

void AMyProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::Action()
{
	if(currentInteractive != nullptr)
	{
		IInteractable::Execute_OnInteract(currentInteractiveActor);
	}
}

void AMyProjectCharacter::OnActorEnter (AActor* interactiveActor)
{
	if(interactiveActor != nullptr)
	{
		bool isInterface = UKismetSystemLibrary::DoesImplementInterface(interactiveActor, UInteractable::StaticClass());

		if(isInterface)
		{
			currentInteractiveActor = interactiveActor;

			currentInteractive = Cast<IInteractable>(interactiveActor);
		}
	}
}

void AMyProjectCharacter::OnLeaveActor ()
{
	currentInteractive = nullptr;
	currentInteractiveActor = nullptr;
}

bool AMyProjectCharacter::FindQuest (FName questID, FQuestItem& quest)
{
	for(int i = 0; i < questList.Num(); i++)
	{
		if(questList[i].QuestID == questID)
		{
			quest = questList[i];
			return true;
		}
	}
	return false;
}

void AMyProjectCharacter::AcceptQuest (FName questID)
{
	bool questFound = false;
	for(int i = 0; i < questList.Num(); i++)
	{
		if(questList[i].QuestID == questID)
		{
			questFound = true;
			break;
		}
	}

	if(!questFound)
	{
		FQuestItem newQuest;
		newQuest.QuestID = questID;
		newQuest.IsCompleted = false;
		questList.Add(newQuest);

		UpdateAndShowQuestList();
	}
}

void AMyProjectCharacter::MarkQuestCompleted (FName questID)
{
	for(int i = 0; i < questList.Num(); i++)
	{
		if((questList[i].QuestID == questID) && (!questList[i].IsCompleted))
		{
			questList[i].IsCompleted = true;
			break;
		}
	}
	
	UpdateAndShowQuestList();

}

void AMyProjectCharacter::UpdateAndShowQuestList ()
{
	AMyProjectGameMode* gameMode = Cast<AMyProjectGameMode>(GetWorld()->GetAuthGameMode());

	if(gameMode != nullptr)
	{
		TArray<FText> questTextList;

		for(int i = 0; i < questList.Num(); i++)
		{
			if(!questList[i].IsCompleted)
			{
				bool success = false;

				FQuest quest = gameMode->FindQuest(questList[i].QuestID, success);

				if(success)
				{
					questTextList.Add(quest.SortDescription);
				}
			}
		}
		OnShowUpdatedQuestList(questTextList);
	}
}

void AMyProjectCharacter::AddItem (FName ItemID)
{
	for(int i = 0; i < equipmentInventory.Num(); i++)
	{
		if(equipmentInventory[i].ItemID == ItemID)
		{
			equipmentInventory[i].Quantity += 1;

			OnRefreshInventory();

			return;
		}
	}

	if(equipmentInventory.Num() == totalEquipmentSlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AHowToCharacter::AddItem] EquipmentInventory full: %d / %d "), equipmentInventory.Num(), totalEquipmentSlots);
		return;
	}

	AMyProjectGameMode* gameMode = Cast<AMyProjectGameMode>(GetWorld()->GetAuthGameMode());

	if(gameMode != nullptr)
	{
		bool found = false;
		FItem itemFound = gameMode->FindItem(ItemID, found);

		FItem newItem;
		newItem.ItemID = ItemID;
		newItem.Name = itemFound.Name;
		newItem.Description = itemFound.Description;
		newItem.Quantity = 1;
		newItem.ItemIcon = itemFound.ItemIcon;

		equipmentInventory.Add(newItem);
	}

	OnRefreshInventory();
}

void AMyProjectCharacter::RemoveItem (FName ItemID)
{
	int32 itemIndexToRemove = -1;

	for(int i = 0; i < equipmentInventory.Num(); i++)
	{
		if(equipmentInventory[i].ItemID == ItemID)
		{
			equipmentInventory[i].Quantity -= 1;

			if(equipmentInventory[i].Quantity <= 0)
			{
				itemIndexToRemove = i;

				break;
			}
		}
	}

	if(itemIndexToRemove >= 0)
	{
		equipmentInventory.RemoveAt(itemIndexToRemove);
	}

	OnRefreshInventory();
}

bool AMyProjectCharacter::HasFreeInventorySlots ()
{
	return (equipmentInventory.Num() < totalEquipmentSlots);
}

bool AMyProjectCharacter::HasItem (FName ItemID)
{
	for(int i = 0; i < equipmentInventory.Num(); i++)
	{
		if(equipmentInventory[i].ItemID == ItemID)
		{
			return true;
		}
	}
	return false;
}

void AMyProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
