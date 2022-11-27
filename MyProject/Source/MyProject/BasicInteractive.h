// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicInteractive.generated.h"

UCLASS()
class MYPROJECT_API ABasicInteractive : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class USceneComponent* rootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicInteractive")
	class UBoxComponent* trigger;

	class AMyProjectCharacter* playerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive")
	FName interactiveName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive")
	FName QuestID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive")
	bool questActivated;
	
public:	
	// Sets default values for this actor's properties
	ABasicInteractive();

protected:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult &SweepResult);

	virtual void OnPlayerBeginOverlap();

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnPlayerEndOverlap();

	

};
