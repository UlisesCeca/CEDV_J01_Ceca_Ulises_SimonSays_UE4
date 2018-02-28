// Fill out your copyright notice in the Description page of Project Settings.

#include "Background.h"
#include "Engine.h"
#include "Runtime/MediaAssets/Public/FileMediaSource.h"


// Sets default values
ABackground::ABackground()
{
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> BarFillObj(TEXT("/Game/Movies/MediaPlayer"));
	MediaPlayer = BarFillObj.Object; 
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComponent");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/musicalblock.musicalblock'"));

	if (MeshAsset.Succeeded())
	{
		StaticMesh->AttachTo(RootComponent);
		StaticMesh->SetStaticMesh(MeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void ABackground::BeginPlay()
{
	Super::BeginPlay();
	PlayVideo();
	
}

void ABackground::PlayVideo() {
	UFileMediaSource* Video = NewObject<UFileMediaSource>();
	Video->SetFilePath(MainVideoFilePath);
	MediaPlayer->OpenSource(Video);
}