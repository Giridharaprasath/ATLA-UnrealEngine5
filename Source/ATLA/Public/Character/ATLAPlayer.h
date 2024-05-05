// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATLACharacterBase.h"

#include "ATLAPlayer.generated.h"

/**
 * ATLA Player Character Base Class.
 */
UCLASS()
class ATLA_API AATLAPlayer : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAPlayer();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void InitAbilityActorInfo() override;
};
