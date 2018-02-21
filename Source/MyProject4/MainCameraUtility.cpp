// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraUtility.h"
#include "kismet/GameplayStatics.h"


// Sets default values
AMainCameraUtility::AMainCameraUtility()
{

}

// Called when the game starts or when spawned
void AMainCameraUtility::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* Player = UGameplayStatics::GetPlayerController(this, 0);

	if (Player) {
		Player->SetViewTarget(MainCamera);
	}
}

