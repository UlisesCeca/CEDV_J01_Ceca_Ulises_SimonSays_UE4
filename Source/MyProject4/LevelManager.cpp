// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"
#include "ConstructorHelpers.h"
#include "CoreTypes.h"
#include "Runtime/MediaAssets/Public/FileMediaSource.h"
#include "Runtime/Engine/Classes/Sound/AmbientSound.h"
#include "Engine.h"


// Sets default values
ALevelManager::ALevelManager()
{
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> BarFillObj(TEXT("/Game/Movies/MediaPlayer"));
	MediaPlayer = BarFillObj.Object;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (AddWidget()) {
		PlayVideo();
		PlayMusic();
	}
}

void ALevelManager::PlayMusic() {
	if (HasMusic) {
		UGameplayStatics::PlaySound2D(GetWorld(), MusicCue, VolumeLevel, 1.0f, 0.0f);
	}
}

void ALevelManager::PlayVideo() {
	if (HasVideo) {
		UFileMediaSource* Video = NewObject<UFileMediaSource>();
		Video->SetFilePath(VideoFilePath);
		MediaPlayer->OpenSource(Video);
	}
}

bool ALevelManager::AddWidget() {
	bool Ok = true;

	if (WidgetName) {
		pWidget = CreateWidget<UUserWidget>(GetGameInstance(), WidgetName);

		if (pWidget.IsValid()) {
			pWidget->AddToViewport();
		}
		else {
			Ok = false;
		}
	}
	else {
		Ok = false;
	}
	return Ok;
}

