// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Background.generated.h"

UCLASS()
class MYPROJECT4_API ABackground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Video settings")
		FString MainVideoFilePath;
	UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UStaticMeshComponent* StaticMesh;

	void PlayVideo();
	
};
