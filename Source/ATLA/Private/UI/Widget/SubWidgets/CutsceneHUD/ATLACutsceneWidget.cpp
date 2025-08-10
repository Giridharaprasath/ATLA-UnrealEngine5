// Copyright Melon Studios.

#include "UI/Widget/SubWidgets/CutsceneHUD/ATLACutsceneWidget.h"

void UATLACutsceneWidget::ShowCutsceneHorizontalBars()
{
	PlayHorizontalFadeAnim(true);
}

void UATLACutsceneWidget::HideCutsceneHorizontalBars()
{
	PlayHorizontalFadeAnim(false);
}

void UATLACutsceneWidget::ShowCutsceneVerticalBars()
{
	PlayVerticalFadeAnim(true);
}

void UATLACutsceneWidget::HideCutsceneVerticalBars()
{
	PlayVerticalFadeAnim(false);
}

void UATLACutsceneWidget::PlayHorizontalFadeAnim_Implementation(const bool bShowBar)
{
}

void UATLACutsceneWidget::PlayVerticalFadeAnim_Implementation(const bool bShowBar)
{
}
