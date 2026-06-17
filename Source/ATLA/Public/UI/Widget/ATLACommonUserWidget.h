// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "ATLACommonUserWidget.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 *	ATLA Common User Widget Class.
 */
UCLASS(Abstract, BlueprintType)
class ATLA_API UATLACommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* GetWidgetStackByTag(const FGameplayTag& InTag) const;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateWidgetStack(UPARAM(meta = ( Categories = "ATLA.UI")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> WidgetStackMap;
};
