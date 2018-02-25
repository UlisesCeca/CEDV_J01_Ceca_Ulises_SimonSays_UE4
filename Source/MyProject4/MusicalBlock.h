// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "MusicalBlock.generated.h"

UCLASS()
class MYPROJECT4_API AMusicalBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicalBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Basic")
		FString BlockName;
	UPROPERTY(EditAnywhere, Category = "Textures")
		UMaterial* DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = "Textures")
		UMaterial* HoverMaterial;
	UPROPERTY(EditAnywhere, Category = "Textures")
		UMaterial* WrongMaterial;
	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundCue* DefaultSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundCue* WrongSound;
	UPROPERTY()
		UStaticMeshComponent* StaticMesh;
	UFUNCTION()
		void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void OnClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	void ChangeTextures();
	void PlaySound();
	void Restart();
	void Play();
	void PlayBadSequence();

};
