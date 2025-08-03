// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enum/ECharacterElement.h"

#include "ATLACharacterInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Primary Attributes")
	bool bUseCustomPrimaryAttributes = false;

	UPROPERTY(EditDefaultsOnly, Category = "Primary Attributes", meta = (EditCondition = "bUseCustomPrimaryAttributes", EditConditionHides))
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Secondary Attributes")
	bool bUseCustomSecondaryAttributes = false;

	UPROPERTY(EditDefaultsOnly, Category = "Secondary Attributes", meta = (EditCondition = "bUseCustomSecondaryAttributes", EditConditionHides))
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Vital Attributes")
	bool bUseCustomVitalAttributes = false;

	UPROPERTY(EditDefaultsOnly, Category = "Vital Attributes", meta = (EditCondition = "bUseCustomVitalAttributes", EditConditionHides))
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CharacterAbilities;
};

USTRUCT(BlueprintType)
struct FCharacterClass
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
	TMap<ECharacterType, FCharacterInfo> Characters;
};

/**
 *	ATLA Character Info Data Asset Class.
 */
UCLASS()
class ATLA_API UATLACharacterInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "ATLA Character Info")
	TMap<ECharacterElement, FCharacterClass> ATLACharacters;

	UPROPERTY(EditDefaultsOnly, Category = "Character Common")
	TSubclassOf<UGameplayEffect> CommonPrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Character Common")
	TSubclassOf<UGameplayEffect> CommonSecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Character Common")
	TSubclassOf<UGameplayEffect> CommonVitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Character Common")
	TArray<TSubclassOf<UGameplayEffect>> CommonAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Character Common")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	FCharacterInfo GetCharacterInfo(const ECharacterElement CharacterElement, const ECharacterType CharacterType);
};
