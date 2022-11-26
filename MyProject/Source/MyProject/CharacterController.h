// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UINavController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ACharacterController : public AUINavController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Action();

	class AMyProjectCharacter* playerCharacter;
	
	
};
