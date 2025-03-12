// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterElement.h"
#include "UObject/Interface.h"

#include "ATLAPlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UATLAPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	ATLA Player Interface Class.
 */
class ATLA_API IATLAPlayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ATLA|Player")
	virtual ECharacterElement GetCharacterElement() const;
	UFUNCTION(BlueprintCallable, Category = "ATLA|Player")
	virtual ECharacterType GetCharacterType() const;
};
