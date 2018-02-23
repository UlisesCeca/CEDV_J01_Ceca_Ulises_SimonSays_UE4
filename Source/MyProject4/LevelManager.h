// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "LevelManager.generated.h"

UCLASS()
class MYPROJECT4_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void PlayVideo();
	void PlayMusic();
	bool AddWidget();
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> WidgetName;
	UPROPERTY(EditAnywhere, Category = "Video settings")
		bool HasVideo;
	UPROPERTY(EditAnywhere, Category = "Video settings")
		FString VideoFilePath;
	UPROPERTY(EditAnywhere, Category = "Music settings")
		bool HasMusic;
	UPROPERTY(EditAnywhere, Category = "Music settings")
		USoundCue* MusicCue;
	UPROPERTY(EditAnywhere, Category = "Music settings")
		float VolumeLevel;
	UPROPERTY(EditAnywhere, Category = "Level settings")
		bool PlayAnotherLevelAfter;
	UPROPERTY(EditAnywhere, Category = "Level settings")
		FString NextLevelName;
	TWeakObjectPtr<class UUserWidget> pWidget;
	UMediaPlayer* MediaPlayer;

};
