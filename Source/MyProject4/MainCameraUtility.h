// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"

#include "MainCameraUtility.generated.h"

UCLASS()
class MYPROJECT4_API AMainCameraUtility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCameraUtility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// To select the camera
	UPROPERTY(EditAnywhere, Category = "Main Camera")
		AActor* MainCamera;
};
