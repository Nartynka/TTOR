// Fill out your copyright notice in the Description page of Project Settings.


#include "TTORGameInstance.h"

void UTTORGameInstance::CompleteLevel(ELevels Level)
{
	CompletedLevels.Add(Level);
}

bool UTTORGameInstance::WasLevelCompleted(ELevels Level)
{
	return CompletedLevels.Contains(Level);
}
