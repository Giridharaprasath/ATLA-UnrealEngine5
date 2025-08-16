// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "FRotationsToTranslation.generated.h"

/**
 *	Rotations To Translation Function Return Struct.
 */
USTRUCT()
struct FRotationsToTranslation
{
	GENERATED_BODY()

	UPROPERTY()
	FVector2D Translation;

	UPROPERTY()
	bool bIsClockwise;

	UPROPERTY()
	bool bIsInRadarSight;

	FRotationsToTranslation(): Translation(FVector2D::ZeroVector), bIsClockwise(false), bIsInRadarSight(false)
	{
	}

	explicit FRotationsToTranslation(const float TranslationX, const bool bIsClockwise, const bool bIsInRadarSight)
	{
		Translation.X = TranslationX;
		this->bIsClockwise = bIsClockwise;
		this-> bIsInRadarSight = bIsInRadarSight;
	}
};
