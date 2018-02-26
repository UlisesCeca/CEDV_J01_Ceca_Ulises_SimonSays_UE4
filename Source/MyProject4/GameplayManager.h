// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicalBlock.h"
#include "GameplayManager.generated.h"

UENUM()
enum class EGameStateEnum : uint8
{
	GE_NotStarted	UMETA(DisplayName = "NOT STARTED"),
	GE_Started		UMETA(DisplayName = "STARTED"),
	GE_Ended		UMETA(DisplayName = "ENDED"),
	GE_Unblocked	UMETA(DisplayName = "UNBLOCKED"),
	GE_Blocked		UMETA(DisplayName = "BLOCKED")
};

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
	EGameStateEnum GameState;
	TArray<EBlockEnum> SoundsSequence;
	TArray<TWeakObjectPtr<AMusicalBlock>> BlocksArray;
	int16 PlayedBlocks;
	int16 Score;
	int8 Lives;
	int8 Level;

	void GenerateRandomSequence();
	void FindBlocks(); 
	void PlayBlocks();
	EGameStateEnum GetGameState();
	
};
