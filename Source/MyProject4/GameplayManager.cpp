// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayManager.h"
#include "Engine.h"
#include "LevelManager.h"
#include "MySaveGame.h"
#include "Record.h"
#include "MusicalBlock.h"
#include "WidgetsManager.h"


// Sets default values
AGameplayManager::AGameplayManager()
{
	PlayedBlocks = 0;
	Score = 0;
	Lives = 2;
	Level = 1;
	GameStarted = false;
}

// Called when the game starts or when spawned
void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();
	GetWidgetsManager();
	FindLevelManager();
	FindBlocks();
	LoadRecords();
	//Prueba();
	WidgetsManager->CreateRecordWidget();
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
	//pWidget->RemoveFromParent();
	WidgetsManager->DeleteRecordWidget();
}

void AGameplayManager::FindBlocks()
{
	for (TActorIterator<AMusicalBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		BlocksArray.Add(Cast<AMusicalBlock>(*ActorItr));

	}
}

void AGameplayManager::FindLevelManager()
{
	for (TActorIterator<ALevelManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		LevelManager = Cast<ALevelManager>(*ActorItr);

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
		IncreaseScore(1);
		if (PlayedBlocks == SoundsSequence.Num()) { //have played all the sounds
			IncreaseScore(6);
			IncreaseLevel();
			PlayNextSequence();
		}
	}
	else {
		PlayedBlock.PlayBadSequence();
		DecreaseLives();
		DecreaseScore();
		if (Lives > 0) {
			ContinueGame();
		}
		else {
			if (!CheckIfNewRecord())
				EndGame();
		}
	}
}

void AGameplayManager::ContinueGame() {
	RestartGame();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AGameplayManager::GenerateRandomSequence, 1.0f, false, 5.0f);
}

void AGameplayManager::EndGame() {
	ResetScore();
	ResetLives();
	RestartGame();
}

void AGameplayManager::RestartGame() {
	GameStarted = false;
	PlayedBlocks = 0;
	ResetLevel();
	DeactivateBlocks();
	SoundsSequence.Empty();
}

void AGameplayManager::IncreaseScore(int amount) {
	Score += amount;
	LevelManager->UpdateWidgetText("scorePoints", FString::FromInt(Score));
}

void AGameplayManager::DecreaseScore() {
	if (Score >= 5)
		Score -= 5;
	LevelManager->UpdateWidgetText("scorePoints", FString::FromInt(Score));
}

void AGameplayManager::ResetScore() {
	Score = 0;
	LevelManager->UpdateWidgetText("scorePoints", FString::FromInt(Score));
}

void AGameplayManager::IncreaseLevel() {
	Level += 1;
	LevelManager->UpdateWidgetText("levelNumber", FString::FromInt(Level));
}

void AGameplayManager::ResetLevel() {
	Level = 1;
	LevelManager->UpdateWidgetText("levelNumber", FString::FromInt(Level));
}

void AGameplayManager::DecreaseLives() {
	Lives -= 1;
	LevelManager->UpdateWidgetText("livesNumber", FString::FromInt(Lives));
}

void AGameplayManager::ResetLives() {
	Lives = 2;
	LevelManager->UpdateWidgetText("livesNumber", FString::FromInt(Lives));
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

void AGameplayManager::LoadRecords()
{
	CheckSaveFileExists();
	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	Records = LoadGameInstance->Records;
}

void AGameplayManager::SaveRecords()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->Records = this->Records;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void AGameplayManager::CheckSaveFileExists()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex)) {
		SaveRecords();
	}
}

bool AGameplayManager::CheckIfNewRecord()
{
	bool NewRecord = false;
	if (Score != 0) {
		if (Records.Num() < 10) {	//if there are still slots we can add a new record
			WidgetsManager->CreateRecordWidget();
			NewRecord = true;
		}
		else {
			for (int i = 0; i < Records.Num(); i++) {
				if (Score > Records[i].GetScore()) {	//if the new record is bigger than other we replace it
					WidgetsManager->CreateRecordWidget();
					RecordToBeReplaced = i;
					NewRecord = true;
					break;
				}
			}
		}
	}
	
	return NewRecord;
}

void AGameplayManager::InsertRecord(FString PlayerName)
{
	FRecord NewRecord(PlayerName, Score, Level);

	if (Records.Num() < 10) {	//if there are still slots we just add a new one and sort the array
		Records.Add(NewRecord);
		Records.Sort();
	}
	else {	//if no slots then we just replace a lower old one for the new higher one
		Records[RecordToBeReplaced] = NewRecord;
	}
	SaveRecords();
	WidgetsManager->DeleteRecordWidget();
	EndGame();
}


void AGameplayManager::GetWidgetsManager() {

	for (TActorIterator<AWidgetsManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		WidgetsManager = Cast<AWidgetsManager>(*ActorItr);

	}
}

void AGameplayManager::AskPlayerAboutLeaving() {

	WidgetsManager->CreateBackToMenuWidget();
}

void AGameplayManager::DeleteBackWidget() {

	WidgetsManager->DeleteBackToMenuWidget();
}

void AGameplayManager::Prueba() {
	if (Widget) {
		pWidget = CreateWidget<UUserWidget>(GetGameInstance(), Widget);

		if (pWidget.IsValid()) {
			pWidget->AddToViewport();
		}
	}
}