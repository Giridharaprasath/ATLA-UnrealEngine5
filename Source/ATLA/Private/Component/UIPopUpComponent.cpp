// Copyright Melon Studios.

#include "Component/UIPopUpComponent.h"
#include "ATLABlueprintFunctionLibrary.h"
#include "Enum/EUIPopUpWidget.h"
#include "Game/ATLAGameInstance.h"
#include "UI/Widget/ATLACommonUserWidget.h"

void UUIPopUpComponent::ShowPopUpWidget(EUIPopUpWidget PopUpWidget)
{
	checkf(WidgetBase, TEXT("Pop Up Widget Class Not Set"));

	CurrentUIPopUpWidget = PopUpWidget;
	FText TitleText;

	switch (CurrentUIPopUpWidget)
	{
	case EUIPopUpWidget::ExitToDesktop:
		TitleText = FText::FromString("Exit To Desktop?");
		break;
	case EUIPopUpWidget::ExitToMainMenu:
		TitleText = FText::FromString("Exit To Main Menu?");
		break;
	default:
		TitleText = FText::FromString("");
		break;
	}

	WidgetBase->PushToPopUpUIStack(FText(TitleText));
}

void UUIPopUpComponent::PopUpWidgetYes()
{
	switch (CurrentUIPopUpWidget)
	{
	case EUIPopUpWidget::ExitToDesktop:
		UATLABlueprintFunctionLibrary::GetATLAGameInstance(this)->ExitToDesktop();
		break;
	case EUIPopUpWidget::ExitToMainMenu:
		UATLABlueprintFunctionLibrary::GetATLAGameInstance(this)->ExitToMainMenu();
		break;
	default:
		break;
	}
}

void UUIPopUpComponent::PopUpWidgetNo()
{
}

void UUIPopUpComponent::SetWidgetBase(UATLACommonUserWidget* Widget)
{
	WidgetBase = Widget;
}
