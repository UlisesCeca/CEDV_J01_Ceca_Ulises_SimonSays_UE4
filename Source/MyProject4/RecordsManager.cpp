// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordsManager.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "Record.h"
#include "MySaveGame.h"


// Sets default values
ARecordsManager::ARecordsManager()
{

}

// Called when the game starts or when spawned
void ARecordsManager::BeginPlay()
{
	Super::BeginPlay();
	LoadWidget();
	LoadRecords();
	GetPlayerNames();
	
}

void ARecordsManager::LoadRecords() {
	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex)) {	// if the save file exists
		LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		Records = LoadGameInstance->Records;
	}
}

void ARecordsManager::ShowRecordsInScreen() {

}

void ARecordsManager::LoadWidget() {
	if (Widget) {
		pWidget = CreateWidget<UUserWidget>(GetGameInstance(), Widget);

		if (pWidget.IsValid()) {
			pWidget->AddToViewport();
		}
	}
}

void ARecordsManager::GetPlayerNames() {
	FString PlayerNames;

	for (int i = 0; i < Records.Num(); i++) {
		PlayerNames += Records[i].GetPlayerName() + "\n";
	}
	if (pWidget.IsValid()) {
		pWidgetTextComponent = (UTextBlock*)pWidget->GetWidgetFromName("PlayersNames");
		pWidgetTextComponent->SetText(FText::FromString(PlayerNames));
	}

	FString Scores;
	for (int i = 0; i < Records.Num(); i++) {
		Scores += FString::FromInt(Records[i].GetScore()) + "\n";
	}
	if (pWidget.IsValid()) {
		pWidgetTextComponent = (UTextBlock*)pWidget->GetWidgetFromName("Scores");
		pWidgetTextComponent->SetText(FText::FromString(Scores));
	}
}