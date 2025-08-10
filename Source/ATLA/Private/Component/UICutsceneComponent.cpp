// Copyright Melon Studios.

#include "Component/UICutsceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/SubWidgets/CutsceneHUD/ATLACutsceneWidget.h"

void UUICutsceneComponent::CreateCutsceneWidgets()
{
	checkf(CutsceneBlackBarsWidgetClass, TEXT("Cutscene Widget Class Not Set In %hs"), __FUNCTION__);

	CutsceneBlackBarsWidget = CreateWidget<UATLACutsceneWidget>(GetWorld(), CutsceneBlackBarsWidgetClass);
	CutsceneBlackBarsWidget->AddToViewport(50);
}

void UUICutsceneComponent::ShowCutsceneHorizontalBars()
{
	checkf(CutsceneBlackBarsWidget, TEXT("Cutscene Widget Not Set In %hs"), __FUNCTION__);

	CutsceneBlackBarsWidget->ShowCutsceneHorizontalBars();
}

void UUICutsceneComponent::HideCutsceneHorizontalBars()
{
	checkf(CutsceneBlackBarsWidget, TEXT("Cutscene Widget Not Set In %hs"), __FUNCTION__);

	CutsceneBlackBarsWidget->HideCutsceneHorizontalBars();
}

void UUICutsceneComponent::ShowCutsceneVerticalBars()
{
	checkf(CutsceneBlackBarsWidget, TEXT("Cutscene Widget Not Set In %hs"), __FUNCTION__);

	CutsceneBlackBarsWidget->ShowCutsceneVerticalBars();
}

void UUICutsceneComponent::HideCutsceneVerticalBars()
{
	checkf(CutsceneBlackBarsWidget, TEXT("Cutscene Widget Not Set In %hs"), __FUNCTION__);

	CutsceneBlackBarsWidget->HideCutsceneVerticalBars();
}
