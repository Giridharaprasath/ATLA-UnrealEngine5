// Copyright Melon Studios.

#include "Component/UICutsceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/PlayerHUD/SubWidgets/CutsceneHUD/ATLACutsceneWidget.h"

void UUICutsceneComponent::CreateCutsceneWidgets()
{
	checkf(CutsceneHorizontalBarsWidgetClass, TEXT("Cutscene Widget Class Not Set In ATLA HUD"));
	CutsceneHorizontalBarsWidget = CreateWidget<UATLACutsceneWidget>(GetWorld(), CutsceneHorizontalBarsWidgetClass);
	CutsceneHorizontalBarsWidget->AddToViewport(50);
}

void UUICutsceneComponent::ShowCutsceneBlackBars()
{
	checkf(CutsceneHorizontalBarsWidget, TEXT("Cutscene Widget Not Set"));

	CutsceneHorizontalBarsWidget->ShowCutsceneBlackBars();
}

void UUICutsceneComponent::HideCutsceneBlackBars()
{
	checkf(CutsceneHorizontalBarsWidget, TEXT("Cutscene Widget Not Set"));

	CutsceneHorizontalBarsWidget->HideCutsceneBlackBars();
}
