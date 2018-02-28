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
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> LostWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> ReadyWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> ListenWidget;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> GoWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pRecordWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pBackdWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pQuitWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pLostWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pReadyWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pListenWidget;
	UPROPERTY()
		TWeakObjectPtr<class UUserWidget> pGoWidget;

	void CreateNewWidget(TSubclassOf<UUserWidget> Widget, TWeakObjectPtr<UUserWidget> pWidget);

public:
	UFUNCTION(BlueprintCallable)
		void CreateRecordWidget();
	UFUNCTION(BlueprintCallable)
		void CreateBackToMenuWidget();
	UFUNCTION(BlueprintCallable)
		void CreateQuitGameWidget();
	UFUNCTION(BlueprintCallable)
		void CreateLostWidget();
	UFUNCTION(BlueprintCallable)
		void CreateReadyWidget();
	UFUNCTION(BlueprintCallable)
		void CreateListenWidget();
	UFUNCTION(BlueprintCallable)
		void CreateGoWidget();
};
