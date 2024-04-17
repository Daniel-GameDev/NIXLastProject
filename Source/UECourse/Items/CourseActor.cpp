// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseActor.h"

// Sets default values
ACourseActor::ACourseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Mesh);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ACourseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACourseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACourseActor::ChangeMesh(AActor* overlappingActor, UStaticMesh* newMesh)
{
	if (overlappingActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		Mesh->SetStaticMesh(newMesh);
	}
}
