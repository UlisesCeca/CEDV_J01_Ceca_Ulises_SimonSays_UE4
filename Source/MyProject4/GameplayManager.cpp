// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayManager.h"
#include "Engine.h"
#include "MusicalBlock.h"


// Sets default values
AGameplayManager::AGameplayManager()
{
	PlayedBlocks = 0;
	Score = 0;
	Lives = 5;
	Level = 0;
	GameStarted = false;
}

// Called when the game starts or when spawned
void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();
	FindBlocks();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::GenerateRandomSequence, 1.0f, false, 5.0f);
}

void AGameplayManager::GenerateRandomSequence()
{
	EBlockEnum NewBlock;
	if (!GameStarted) {
		for (int i = 0; i < 4; i++) {
			NewBlock = static_cast<EBlockEnum>(FMath::RandRange(0, 3));
			SoundsSequence.Add(NewBlock);
		}
	}
	else {
		NewBlock = static_cast<EBlockEnum>(FMath::RandRange(0, 3));
		SoundsSequence.Add(NewBlock);
	}
	GameStarted = true;
	GetWorldTimerManager().ClearTimer(TimerHandler);
	PlayBlocks();
}

void AGameplayManager::FindBlocks()
{
	for (TActorIterator<AMusicalBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		BlocksArray.Add(Cast<AMusicalBlock>(*ActorItr));

	}
}

void AGameplayManager::PlayBlocks()
{
	if (PlayedBlocks < SoundsSequence.Num()) {	//we play the block if there are still sounds to be played
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::PlayBlocks, 1.0f, false, 1.0f);	//we wait to play next block
		for (int j = 0; j < BlocksArray.Num(); j++) {
			BlocksArray[j]->Play(SoundsSequence[PlayedBlocks]);
		}
		PlayedBlocks += 1;
	}
	else {
		PlayedBlocks = 0;
		GetWorldTimerManager().ClearTimer(TimerHandler);	//if all blocks have been played then we restart the timer
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::ActivateBlocks, 1.0f, false, 5.0f);	//we activate the blocks so the player can play them
	}
}

void AGameplayManager::CheckPlayedBlock(AMusicalBlock &PlayedBlock)
{
	if (PlayedBlock.GetBlockName() == SoundsSequence[PlayedBlocks]) {
		PlayedBlocks += 1;
		Score += 1;
		if (PlayedBlocks == SoundsSequence.Num()) { //have played all the sounds
			PlayNextSequence();
		}
	}
	else {
		PlayedBlock.PlayBadSequence();
		RestartGame();
	}
}

void AGameplayManager::RestartGame() {
	GameStarted = false;
	PlayedBlocks = 0;
	Score = 0;
	Lives = 5;
	DeactivateBlocks();
	SoundsSequence.Empty();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::GenerateRandomSequence, 1.0f, false, 5.0f);
}

void AGameplayManager::ActivateBlocks()
{
	for (int j = 0; j < BlocksArray.Num(); j++) {
		BlocksArray[j]->ActivateBlock();
	}
	GetWorldTimerManager().ClearTimer(TimerHandler);	//if all blocks have been activated then we restart the timer
}

void AGameplayManager::DeactivateBlocks()
{
	for (int j = 0; j < BlocksArray.Num(); j++) {
		BlocksArray[j]->DeactivateBlock();
	}
}

void AGameplayManager::PlayNextSequence()
{
	PlayedBlocks = 0;
	DeactivateBlocks();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::GenerateRandomSequence, 1.0f, false, 5.0f);
}
