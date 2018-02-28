// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Record.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "RecordsManager.generated.h"

class ALevelManager;

UCLASS()
class MYPROJECT4_API ARecordsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> Widget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pWidget;
	TArray<FRecord> Records;
	TWeakObjectPtr<class UTextBlock> pWidgetTextComponent;

	void GetPlayerNames();
	void GetScores();
	void GetLevels();
	void LoadRecords();
	void ShowRecordsInScreen();
	void LoadWidget();
	
	
};
