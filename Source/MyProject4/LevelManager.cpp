// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"
#include "ConstructorHelpers.h"
#include "CoreTypes.h"
#include "Runtime/MediaAssets/Public/FileMediaSource.h"
#include "Runtime/Engine/Classes/Sound/AmbientSound.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectBaseUtility.h"
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
	MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	SetCursor();
	if (HasMainCamera) 
		SetMainCamera();
	
	if (AddWidget()) 
		if (HasMainVideo)
			PlayVideo();
	
	if (HasMusic)
		PlayMusic();

	if (PlayAnotherLevelAfterMainVideo)
		GetWorldTimerManager().SetTimer(TimerHandler, this, &ALevelManager::OpenNextLevel, 1.0f, false, MainVideoDuration);
}

void ALevelManager::OpenNextLevel() {
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	GetWorldTimerManager().ClearTimer(TimerHandler);
}

void ALevelManager::PlayMusic() {
		UGameplayStatics::PlaySound2D(GetWorld(), MusicCue, VolumeLevel, 1.0f, 0.0f);
	
}

void ALevelManager::PlayVideo() {
	UFileMediaSource* Video = NewObject<UFileMediaSource>();
	Video->SetFilePath(MainVideoFilePath);
	MediaPlayer->OpenSource(Video);

	if (PlayAnotherLevelAfterMainVideo)
		MainVideoDuration = MusicCue->GetDuration();
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

void ALevelManager::SetCursor() {
	if (MyController) {
		MyController->bShowMouseCursor = ShowCursor;
		MyController->bEnableClickEvents = ShowCursor;
		MyController->bEnableMouseOverEvents = ShowCursor;
	}
}

void ALevelManager::SetMainCamera() {
	if (MyController) {
		MyController->SetViewTarget(MainCamera);
	}
}
