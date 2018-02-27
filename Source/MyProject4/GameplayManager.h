// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EBlockEnum.h"
#include "GameplayManager.generated.h"

class AMusicalBlock;


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
	int16 PlayedBlocks;
	int16 Score;
	int8 Lives;
	int8 Level;

	void PlayNextSequence();
	void GenerateRandomSequence();
	void FindBlocks(); 
	void PlayBlocks();
	void ActivateBlocks();
	void DeactivateBlocks();
	void RestartGame();

public:
	void CheckPlayedBlock(AMusicalBlock &PlayedBlock);
};
