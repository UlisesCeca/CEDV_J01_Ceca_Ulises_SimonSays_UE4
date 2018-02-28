// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Record.h"
#include "RecordsManager.generated.h"

UCLASS()
class MYPROJECT4_API ARecordsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordsManager();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
