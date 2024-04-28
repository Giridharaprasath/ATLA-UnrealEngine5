// Copyright Melon Studios.


#include "UI/WidgetController/ATLAWidgetController.h"

void UATLAWidgetController::SetWidgetController(const FWidgetController& WidgetController)
{
	PlayerController = WidgetController.PlayerController;
	PlayerState = WidgetController.PlayerState;
	AbilitySystemComponent = WidgetController.AbilitySystemComponent;
	AttributeSet = WidgetController.AttributeSet;
}

void UATLAWidgetController::BroadcastInitialValues()
{
	
}

void UATLAWidgetController::BindCallbacksToDependencies()
{
	
}
