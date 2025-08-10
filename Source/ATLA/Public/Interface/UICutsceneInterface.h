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
	virtual void ShowCutsceneHorizontalBars() = 0;
	virtual void HideCutsceneHorizontalBars() = 0;
	virtual void ShowCutsceneVerticalBars() = 0;
	virtual void HideCutsceneVerticalBars() = 0;
};
