// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "WidgetsManager.generated.h"


UCLASS()
class MYPROJECT4_API AWidgetsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetsManager();	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> RecordWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> BacToMenukWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> QuitGameWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pRecordWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pBackdWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pQuitWidget;

	void CreateNewWidget(TSubclassOf<UUserWidget> Widget, TWeakObjectPtr<UUserWidget> pWidget);

public:
	UFUNCTION(BlueprintCallable)
		void CreateRecordWidget();
	UFUNCTION(BlueprintCallable)
		void CreateBackToMenuWidget();
	UFUNCTION(BlueprintCallable)
		void CreateQuitGameWidget();
};
