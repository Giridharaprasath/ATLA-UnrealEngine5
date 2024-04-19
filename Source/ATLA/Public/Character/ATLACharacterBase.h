// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ATLACharacterBase.generated.h"

/**
 * ATLA Character Base Class.
 */
UCLASS(Abstract)
class ATLA_API AATLACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AATLACharacterBase();

protected:
	virtual void BeginPlay() override;
};
