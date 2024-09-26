// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "ATLA.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogATLA, Log, All);

USTRUCT(BlueprintType)
struct FATLACharacters : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString CharacterName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AATLAPlayer> CharacterClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharacterImage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FColor CharacterColor;
};
