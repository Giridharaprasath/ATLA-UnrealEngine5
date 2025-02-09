// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

/**
 *	ATLA UI Pop Up Widget Enum Class.
 */
UENUM(BlueprintType, Category = "ATLA|UI|Pop Up")
enum class EUIPopUpWidget : uint8
{
	None UMETA(DisplayName = "None"),
	ExitToDesktop UMETA(DisplayName = "Exit To Desktop"),
	ExitToMainMenu UMETA(DisplayName = "Exit To Main Menu")
};
