// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * ATLA Combat Interface Class.
 */
class ATLA_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();
};
