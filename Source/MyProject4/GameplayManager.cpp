// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayManager.h"
#include "Engine.h"


// Sets default values
AGameplayManager::AGameplayManager()
{
	score = 0;
	lives = 5;
	level = 0;
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
	IterateOverSoundsAndBlocksToBePlayed();
}

void AGameplayManager::FindBlocks()
{
	for (TActorIterator<AMusicalBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		BlocksArray.Add(Cast<AMusicalBlock>(*ActorItr));

	}
}

void AGameplayManager::IterateOverSoundsAndBlocksToBePlayed()
{
	int SoundIndex;
	int BlockIndex;
	for (int i = 0; i < SoundsSequence.Num(); i++) {
		for (int j = 0; j < BlocksArray.Num(); j++) {
			PlayBlock(SoundsSequence[i], BlocksArray[j]);
		}
	}
}

void AGameplayManager::PlayBlock(int SoundIndex, int BlockIndex)
{
	BlocksArray[SoundIndex]->Play(SoundsSequence[BlockIndex]);
}