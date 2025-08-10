// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "FWorldDirection.generated.h"

/**
 *	Radar System World Direction Structure Class.
 */
USTRUCT(BlueprintType, Category = "Radar")
struct FWorldDirection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DirectionName = FText();
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int WorldRotation = 0;

	FWorldDirection()
	{
	}

	FWorldDirection(const FText& DirectionName, const int WorldRotation)
	{
		this->DirectionName = DirectionName;
		this->WorldRotation = WorldRotation;
	}
};
