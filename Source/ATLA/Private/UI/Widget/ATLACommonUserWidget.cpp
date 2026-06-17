// Copyright Melon Studios.

#include "UI/Widget/ATLACommonUserWidget.h"
#include "ATLA/ATLA.h"

UCommonActivatableWidgetContainerBase* UATLACommonUserWidget::GetWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(WidgetStackMap.Contains(InTag), TEXT("GG : Can't find the widget stack by tag %s"), *InTag.ToString());

	return WidgetStackMap.FindRef(InTag);
}

void UATLACommonUserWidget::CreateWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (IsDesignTime()) return;

	if (WidgetStackMap.Contains(InStackTag)) return;

	WidgetStackMap.Add(InStackTag, InStack);
	ATLAPrint(TEXT("GG : Created Widget Stack of Tag : ") + InStackTag.ToString(), -1, 7.f, FColor::Green);
}
