// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ATLACutsceneWidget.generated.h"

/**
 *	ATLA Cutscene Widget Class. 
 */
UCLASS()
class ATLA_API UATLACutsceneWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	void ShowCutsceneHorizontalBars();
	void HideCutsceneHorizontalBars();
	void ShowCutsceneVerticalBars();
	void HideCutsceneVerticalBars();

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|UI")
	void PlayHorizontalFadeAnim(const bool bShowBar);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|UI")
	void PlayVerticalFadeAnim(const bool bShowBar);
};
