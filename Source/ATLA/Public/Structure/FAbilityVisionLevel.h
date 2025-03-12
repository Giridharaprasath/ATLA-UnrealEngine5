// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "FAbilityVisionLevel.generated.h"

class UCurveVector;

/**
 *	ATLA Ability Vision Level Class.
 */
USTRUCT(BlueprintType, Category = "ATLA|Ability|Vision")
struct FAbilityVisionLevel : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Radius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Duration;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCurveVector* CurveVector;
};