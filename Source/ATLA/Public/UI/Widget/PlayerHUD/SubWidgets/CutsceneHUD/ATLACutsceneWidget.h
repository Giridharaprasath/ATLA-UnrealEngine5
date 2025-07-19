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
	UFUNCTION(BlueprintImplementableEvent, Category = "ATLA|UI")
	void ShowCutsceneBlackBars();
	UFUNCTION(BlueprintImplementableEvent, Category = "ATLA|UI")
	void HideCutsceneBlackBars();
};
