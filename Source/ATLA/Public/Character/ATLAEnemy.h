// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATLACharacterBase.h"

#include "ATLAEnemy.generated.h"

/**
 * ATLA Enemy Character Base Class.
 */
UCLASS()
class ATLA_API AATLAEnemy : public AATLACharacterBase
{
	GENERATED_BODY()

public:
	AATLAEnemy();

protected:
	virtual void BeginPlay() override;
};
