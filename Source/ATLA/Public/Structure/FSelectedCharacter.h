// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"

#include "FSelectedCharacter.generated.h"

enum class ECharacterElement : uint8;

/**
 *	ATLA Selected Character Structure Class.	 
 */
USTRUCT(BlueprintType, Category = "ATLA|Character")
struct FSelectedCharacter
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsSelected = false;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECharacterElement CharacterElement;

	FSelectedCharacter(): CharacterElement()
	{
	}

	FSelectedCharacter(const bool bInIsSelected, const ECharacterElement InCharacterElement)
	{
		bIsSelected = bInIsSelected;
		CharacterElement = InCharacterElement;
	}

	bool operator==(const FSelectedCharacter& NewSelectedCharacter) const
	{
		return CharacterElement == NewSelectedCharacter.CharacterElement;
	}
};
