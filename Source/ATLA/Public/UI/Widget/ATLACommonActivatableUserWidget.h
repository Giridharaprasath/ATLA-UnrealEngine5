// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/ATLACommonActivatableWidget.h"
#include "ATLACommonActivatableUserWidget.generated.h"

/**
 *	ATLA Common Activatable User Widget Class.
 */
UCLASS()
class ATLA_API UATLACommonActivatableUserWidget : public UATLACommonActivatableWidget
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
