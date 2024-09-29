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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();
};
