// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create all components
	this->sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	this->RootComponent = sceneComponent;

	this->itemMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	this->itemMesh->AttachTo(this->RootComponent);

	this->rotationRate = FRotator(0.0f, 180.f, 0.0f);

	this->boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	this->boxCollider->SetGenerateOverlapEvents(true);
	this->boxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APickUpActor::OnOverlapBegin);
	this->boxCollider->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	speed = 1.0f;
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotate the object (local rotation)
	this->AddActorLocalRotation(this->rotationRate * DeltaTime * speed);
}

void APickUpActor::Show(bool visible)
{
	ECollisionEnabled::Type collision = visible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;

	this->SetActorTickEnabled(visible);

	this->itemMesh->SetVisibility(visible);
	this->itemMesh->SetCollisionEnabled(collision);

	this->boxCollider->SetCollisionEnabled(collision);
}


void APickUpActor::OnInteract()
{
	FString pickUp = FString::Printf(TEXT("Picked up: %s"), *pickUpActorName);

	AMyProjectCharacter* player = Cast<AMyProjectCharacter>(UGamePlayStatics::GetPlayerCharacter(this, 0));
	
	if (player)
	{
		Show(false);

		player->AddToInventory(this);
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, *pickUp);
}

void APickUpActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//check if the other actor is not me and if it is not NULL
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		OnInteract();
	}
}