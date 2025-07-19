// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UICutsceneInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UUICutsceneInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	ATLA UI Cutscene Interface Class.
 */
class ATLA_API IUICutsceneInterface
{
	GENERATED_BODY()

public:
	virtual void ShowCutsceneBlackBars() = 0;
	virtual void HideCutsceneBlackBars() = 0;
};
