// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicalBlock.h"
#include "EngineMinimal.h"


// Sets default values
AMusicalBlock::AMusicalBlock()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/musicalblock.musicalblock'"));

	if (MeshAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshAsset.Object);
	}
}

