// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "FATLACharacters.generated.h"

/**
 *	ATLA Character Structure Class.
 */
USTRUCT(BlueprintType, Category = "ATLA|Character")
struct FATLACharacters : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString CharacterName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class AATLAPlayer> CharacterClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharacterImage = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FColor CharacterColor = FColor::White;
};
