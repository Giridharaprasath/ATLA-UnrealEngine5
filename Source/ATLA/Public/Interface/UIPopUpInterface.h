// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "UIPopUpInterface.generated.h"

class UATLACommonUserWidget;
enum class EUIPopUpWidget : uint8;

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UUIPopUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	ATLA UI Pop Up Interface Class.
 */
class ATLA_API IUIPopUpInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI|Pop Up")
	virtual void ShowPopUpWidget(EUIPopUpWidget PopUpWidget) = 0;
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI|Pop Up")
	virtual void PopUpWidgetYes() = 0;
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI|Pop Up")
	virtual void PopUpWidgetNo() = 0;
};
