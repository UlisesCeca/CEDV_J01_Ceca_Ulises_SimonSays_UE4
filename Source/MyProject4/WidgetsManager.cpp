// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetsManager.h"
#include "TextWidgetTypes.h"
#include "CoreTypes.h"
#include "Engine.h"


// Sets default values
AWidgetsManager::AWidgetsManager()
{
}

// Called when the game starts or when spawned
void AWidgetsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWidgetsManager::CreateNewWidget(TSubclassOf<UUserWidget> Widget, TWeakObjectPtr<UUserWidget> pWidget) {
	if (Widget) {
		pWidget = CreateWidget<UUserWidget>(GetGameInstance(), Widget);

		if (pWidget.IsValid()) {
			pWidget->AddToViewport();
		}
	}
}

void AWidgetsManager::DeleteWidget(TWeakObjectPtr<UUserWidget> pWidget) {
	if (pWidget.IsValid()) {
		pWidget->RemoveFromViewport();
	}
}

void AWidgetsManager::CreateRecordWidget() {
	CreateNewWidget(RecordWidget, pRecordWidget);
}

void AWidgetsManager::CreateBackToMenuWidget() {
	CreateNewWidget(BacToMenukWidget, pBackdWidget);
}

void AWidgetsManager::CreateQuitGameWidget() {
	CreateNewWidget(QuitGameWidget, pQuitWidget);
}

void AWidgetsManager::DeleteRecordWidget() {
	DeleteWidget(pRecordWidget);
}

void AWidgetsManager::DeleteBackToMenuWidget() {
	DeleteWidget(pBackdWidget);
}

void AWidgetsManager::DeleteQuitGameWidget() {
	DeleteWidget(pQuitWidget);
}