// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ATLALoadingWidget.generated.h"

/**
 *	ATLA Loading Widget Class.
 */
UCLASS()
class ATLA_API UATLALoadingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowBlurredLoadingPage();
	void HideBlurredLoadingPage();

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|UI")
	void PlayBlurredLoadingPageAnim(const bool bShowLoadingPage);
};
