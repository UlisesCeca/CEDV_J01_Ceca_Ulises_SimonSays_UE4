// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicalBlock.h"
#include "Engine.h"
#include "EngineMinimal.h"


// Sets default values
AMusicalBlock::AMusicalBlock()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/musicalblock.musicalblock'"));

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

	if (StaticMesh->GetStaticMesh())
		StaticMesh->SetMaterial(0, DefaultMaterial);
}

void AMusicalBlock::CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMesh->SetMaterial(0, HoverMaterial);
}

void AMusicalBlock::CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	StaticMesh->SetMaterial(0, DefaultMaterial);
}

void AMusicalBlock::OnClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UGameplayStatics::PlaySound2D(GetWorld(), DefaultSound, 1.0f, 1.0f, 0.0f);
}

void AMusicalBlock::Play(EBlockEnum PlayedBlock)
{
	if (PlayedBlock == Block) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You've killed all enemies without being hit!!"));
		UGameplayStatics::PlaySound2D(GetWorld(), DefaultSound, 1.0f, 1.0f, 0.0f);
	}
}
