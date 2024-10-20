// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "ATLAGameplayAbility.generated.h"

/**
 *	ATLA Gameplay Ability Class.			
 */
UCLASS()
class ATLA_API UATLAGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "ATLA|Input")
	FGameplayTag StartUpInputTag;
};
