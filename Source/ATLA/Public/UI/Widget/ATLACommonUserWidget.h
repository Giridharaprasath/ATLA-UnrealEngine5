// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"

#include "ATLACommonUserWidget.generated.h"

class UATLACommonActivatableWidget;

/**
 *	ATLA Common UI User Widget Class.
 */
UCLASS()
class ATLA_API UATLACommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|UI")
	void PushToMenuUIStack(TSubclassOf<UATLACommonActivatableWidget> ActivatableWidgetClass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|UI")
	void PushToPopUpUIStack(const FText& TitleText);
};
