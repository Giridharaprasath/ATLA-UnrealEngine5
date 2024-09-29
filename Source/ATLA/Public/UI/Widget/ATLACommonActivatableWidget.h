// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "ATLACommonActivatableWidget.generated.h"

/**
 *	ATLA Common Activatable Widget Class.
 */
UCLASS()
class ATLA_API UATLACommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|UI")
	void ReturnFocusBackToGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|UI")
	void SetMouseCursorState(bool bShowMouseCursor);
};
