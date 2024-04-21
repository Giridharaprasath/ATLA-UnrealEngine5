// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ATLAUserWidget.generated.h"

/**
 * ATLA User Widget Base Class.
 */
UCLASS()
class ATLA_API UATLAUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
