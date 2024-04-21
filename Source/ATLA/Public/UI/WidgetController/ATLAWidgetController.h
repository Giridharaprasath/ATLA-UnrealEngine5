// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ATLAWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * ATLA User Widget Controller Class.
 */
UCLASS()
class ATLA_API UATLAWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
