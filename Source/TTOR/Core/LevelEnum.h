#pragma once

UENUM(BlueprintType)
enum class ELevels : uint8
{
	EL_HUB UMETA(DisplayName = "HUB"),
	EL_Water UMETA(DisplayName = "Water"),
	EL_Fire UMETA(DisplayName = "Fire"),
	EL_Ghost UMETA(DisplayName = "Ghost"),
	EL_Dark UMETA(DisplayName = "Dark")
};