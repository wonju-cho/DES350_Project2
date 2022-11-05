// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PickUpActor.generated.h"

UCLASS()
class MYPROJECT_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Show(bool visible);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Rotationrate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FRotator rotationRate;

	//SceneComponent as Root
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	USceneComponent* sceneComponent;

	//MeshComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UStaticMeshComponent* itemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	float speed;

	UPROPERTY(EditAnywhere)
	UBoxComponent* boxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	FString pickUpActorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	UTexture2D* pickUpActorImage;

	virtual void OnInteract();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
