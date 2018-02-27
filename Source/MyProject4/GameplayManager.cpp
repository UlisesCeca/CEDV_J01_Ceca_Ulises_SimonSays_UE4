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
	GameState = EGameStateEnum::GE_NotStarted;
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
	if (GameState == EGameStateEnum::GE_NotStarted) {
		GameState = EGameStateEnum::GE_Blocked;	//so the player can't do anything on the blocks
		for (int i = 0; i < 4; i++) {
			NewBlock = static_cast<EBlockEnum>(FMath::RandRange(0, 3));
			SoundsSequence.Add(NewBlock);
		}
	}
	else {
		GameState = EGameStateEnum::GE_Blocked;
		NewBlock = static_cast<EBlockEnum>(FMath::RandRange(0, 3));
		SoundsSequence.Add(NewBlock);
	}
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
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::PlayBlocks, 1.0f, false, 1.0f);	//we wait 2s to play next block
		for (int j = 0; j < BlocksArray.Num(); j++) {
			BlocksArray[j]->Play(SoundsSequence[PlayedBlocks]);
		}
		PlayedBlocks += 1;
	}
	else {
		PlayedBlocks = 0;
		GetWorldTimerManager().ClearTimer(TimerHandler);	//if all blocks have been played then we disable the timer
		for (int j = 0; j < BlocksArray.Num(); j++) {
			BlocksArray[j]->SetIsActive(true);
		}
	}
}

EGameStateEnum AGameplayManager::GetGameState()
{
	return GameState;
}