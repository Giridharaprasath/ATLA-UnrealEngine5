// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(LogATLA, Log, All);

static void ATLAPrint(const FString& Message, const int32 InKey = -1, const float InTimeToDisplay = 5.f, const FColor& InColor = FColor::MakeRandomColor())
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InTimeToDisplay, InColor, Message);
		UE_LOG(LogATLA, Log, TEXT("%s"), *Message);
	}
}
