// Copyright Melon Studios.


#include "UI/Widget/SubWidgets/LoadingHUD/ATLALoadingWidget.h"

void UATLALoadingWidget::ShowBlurredLoadingPage()
{
	PlayBlurredLoadingPageAnim(true);
}

void UATLALoadingWidget::HideBlurredLoadingPage()
{
	PlayBlurredLoadingPageAnim(false);
}

void UATLALoadingWidget::PlayBlurredLoadingPageAnim_Implementation(const bool bShowLoadingPage)
{
}
