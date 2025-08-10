// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UILoadingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UUILoadingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	ATLA UI Loading Interface Class.
 */
class ATLA_API IUILoadingInterface
{
	GENERATED_BODY()

public:
	virtual void ShowBlurredLoadingPage() = 0;
	virtual void HideBlurredLoadingPage() = 0;
	virtual void ShowClearLoadingPage() = 0;
	virtual void HideClearLoadingPage() = 0;
};
