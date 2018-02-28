// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EBlockEnum.h"
#include "Record.h"
#include "GameplayManager.generated.h"

class AMusicalBlock;
class ALevelManager;
class AWidgetsManager;


UCLASS()
class MYPROJECT4_API AGameplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandler;
	bool GameStarted;
	TArray<EBlockEnum> SoundsSequence;
	TArray<TWeakObjectPtr<AMusicalBlock>> BlocksArray;
	TWeakObjectPtr<ALevelManager> LevelManager;
	int16 PlayedBlocks;
	int16 Score;
	int8 Lives;
	int8 Level;
	TArray<FRecord> Records;
	int8 RecordToBeReplaced;

	void PlayNextSequence();
	void GenerateRandomSequence();
	void FindBlocks();
	void FindLevelManager();
	void PlayBlocks();
	void ActivateBlocks();
	void DeactivateBlocks();
	void ContinueGame();
	void IncreaseScore(int amount);
	void DecreaseScore();
	void ResetScore();
	void DecreaseLives();
	void ResetLives();
	void IncreaseLevel();
	void ResetLevel();
	void RestartGame();
	void LoadRecords();
	void SaveRecords();
	void CheckSaveFileExists();

public:
	void CheckPlayedBlock(AMusicalBlock &PlayedBlock);
	UFUNCTION(BlueprintCallable)
		void InsertRecord(FString PlayerName);
	UFUNCTION(BlueprintCallable)
		bool CheckIfNewRecord();
	UFUNCTION(BlueprintCallable)
		void EndGame();
};
