// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, Category = "ATLA|Character")
enum class ECharacterElement : uint8
{
	Air UMETA(DisplayName = "Air"),
	Water UMETA(DisplayName = "Water"),
	Earth UMETA(DisplayName = "Earth"),
	Fire UMETA(DisplayName = "Fire"),
	NonBender UMETA(DisplayName = "Non Bender"),
};

UENUM(BlueprintType, Category = "ATLA|Character")
enum class ECharacterType : uint8
{
	Mage UMETA(DisplayName = "Mage"),
};