// Copyright Melon Studios.

#include "UI/Widget/ATLAUserWidget.h"

void UATLAUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
