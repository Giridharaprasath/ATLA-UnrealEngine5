// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterElement.h"

#include "FATLACharacters.generated.h"

enum class ECharacterType : uint8;
enum class ECharacterElement : uint8;
class AATLAPlayer;

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
	ECharacterElement CharacterElement = ECharacterElement::Air;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ECharacterType CharacterType = ECharacterType::Mage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AATLAPlayer> CharacterClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* CharacterImage = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FColor CharacterColor = FColor::White;
};
