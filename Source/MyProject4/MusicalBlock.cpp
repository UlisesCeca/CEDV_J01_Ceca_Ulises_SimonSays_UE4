// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicalBlock.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "GameplayManager.h"


// Sets default values
AMusicalBlock::AMusicalBlock()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/musicalblock.musicalblock'"));
	IsActive = false;

	if (MeshAsset.Succeeded())
	{
		StaticMesh->AttachTo(RootComponent);
		StaticMesh->SetStaticMesh(MeshAsset.Object);
		StaticMesh->OnBeginCursorOver.AddDynamic(this, &AMusicalBlock::CustomOnBeginMouseOver);
		StaticMesh->OnEndCursorOver.AddDynamic(this, &AMusicalBlock::CustomOnEndMouseOver);
		StaticMesh->OnClicked.AddDynamic(this, &AMusicalBlock::OnClick);
	}

}

// Called when the game starts or when spawned
void AMusicalBlock::BeginPlay()
{
	Super::BeginPlay();

	FindGameplayManager();

	if (StaticMesh->GetStaticMesh())
		StaticMesh->SetMaterial(0, DefaultMaterial);
}

void AMusicalBlock::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (IsActive) {
		StaticMesh->SetMaterial(0, HoverMaterial);
	}
}

void AMusicalBlock::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (IsActive) {
		StaticMesh->SetMaterial(0, DefaultMaterial);
	}
}

void AMusicalBlock::OnClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (IsActive) {
		UGameplayStatics::PlaySound2D(GetWorld(), DefaultSound, 1.0f, 1.0f, 0.0f);
		GameplayManager->CheckPlayedBlock(*this);
	}
}

void AMusicalBlock::Play(EBlockEnum PlayedBlock)
{
	if (PlayedBlock == Block) {
		UGameplayStatics::PlaySound2D(GetWorld(), DefaultSound, 1.0f, 1.0f, 0.0f);
		StaticMesh->SetMaterial(0, HoverMaterial);
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AMusicalBlock::SetDefaultMaterial, 1.0f, false, 0.5f); // back to default material
	}
}

void AMusicalBlock::SetDefaultMaterial()
{
	StaticMesh->SetMaterial(0, DefaultMaterial);
	GetWorldTimerManager().ClearTimer(TimerHandler);
}

void AMusicalBlock::ActivateBlock()
{
	IsActive = true;
}

void AMusicalBlock::DeactivateBlock()
{
	IsActive = false;
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AMusicalBlock::SetDefaultMaterial, 1.0f, false, 0.5f); // back to default material for last played block
}

void AMusicalBlock::FindGameplayManager()
{
	for (TActorIterator<AGameplayManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		GameplayManager = Cast<AGameplayManager>(*ActorItr);
	}
}

void AMusicalBlock::PlayBadSequence()
{
	//UGameplayStatics::PlaySound2D(GetWorld(), DefaultSound, 1.0f, 1.0f, 0.0f);
	StaticMesh->SetMaterial(0, WrongMaterial);
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AMusicalBlock::SetDefaultMaterial, 1.0f, false, 0.5f); // back to default material
}


EBlockEnum AMusicalBlock::GetBlockName()
{
	return Block;
}