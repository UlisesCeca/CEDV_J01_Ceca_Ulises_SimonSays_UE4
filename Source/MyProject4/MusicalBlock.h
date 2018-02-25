// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "MusicalBlock.generated.h"

UCLASS()
class MYPROJECT4_API AMusicalBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicalBlock();

private:
	UPROPERTY(EditAnywhere, Category = "Basic")
		FString BlockName;
	UPROPERTY(EditAnywhere, Category = "Textures")
		UTexture* DefaultTexture;
	UPROPERTY(EditAnywhere, Category = "Textures")
		UTexture* WongTexture;
	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundCue* DefaultSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundCue* WrongSound;
	UPROPERTY()
		TWeakObjectPtr<UStaticMeshComponent> StaticMesh;
	void ChangeTextures();
	void PlaySound();
	void Restart();
	void Play();
	void PlayBadSequence();

};
