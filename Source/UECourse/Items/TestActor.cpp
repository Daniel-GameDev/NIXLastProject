// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Mesh);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");

	static ConstructorHelpers::FClassFinder<UUserWidget> hudWidgetObj(TEXT("/Game/Course/Lesson7/UMG_3DWidget"));

	if (hudWidgetObj.Succeeded())
	{
		WidgetClass = hudWidgetObj.Class;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SelectableActorHUD not found !");
		}
		WidgetClass = nullptr;
	}
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair"));
	UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);

	Mesh->SetStaticMesh(mesh);

	BoxCollision->SetHiddenInGame(false);
	BoxCollision->SetBoxExtent(FVector(200.f, 200.f, 100.f));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATestActor::OnOverlapEnd);

	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetWidgetClass(WidgetClass);
	WidgetComponent->SetVisibility(true);
	WidgetComponent->RegisterComponent();
}

void ATestActor::OnConstruction(const FTransform& Transform)
{
	int t = 0;
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	if (otherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Props/SM_Couch.SM_Couch"));
		Mesh->SetStaticMesh(mesh);
	}
}

void ATestActor::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int otherBodyIndex)
{
	if (otherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair"));
		Mesh->SetStaticMesh(mesh);
	}
}
