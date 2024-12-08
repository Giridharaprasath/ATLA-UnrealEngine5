// Copyright Melon Studios.

#include "UI/Widget/ATLACommonActivatableUserWidget.h"

void UATLACommonActivatableUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
