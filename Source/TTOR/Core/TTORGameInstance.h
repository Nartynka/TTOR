// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LevelEnum.h"
#include "TTORGameInstance.generated.h"

UCLASS()
class TTOR_API UTTORGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<ELevels> CompletedLevels;

	UFUNCTION(BlueprintCallable)
	void CompleteLevel(ELevels Level);

	bool WasLevelCompleted(ELevels Level);

};
