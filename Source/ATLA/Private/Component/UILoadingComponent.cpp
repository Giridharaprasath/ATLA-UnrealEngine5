// Copyright Melon Studios.

#include "Component/UILoadingComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/SubWidgets/LoadingHUD/ATLALoadingWidget.h"

void UUILoadingComponent::CreateLoadingWidgets()
{
	checkf(LoadingWidgetClass, TEXT("Loading Widget Class Not Set In %hs"), __FUNCTION__);

	LoadingWidget = CreateWidget<UATLALoadingWidget>(GetWorld(), LoadingWidgetClass);
	LoadingWidget->AddToViewport(50);
}

void UUILoadingComponent::ShowBlurredLoadingPage()
{
	checkf(LoadingWidget, TEXT("Loading Widget Not Set In %hs"), __FUNCTION__);

	LoadingWidget->ShowBlurredLoadingPage();
}

void UUILoadingComponent::HideBlurredLoadingPage()
{
	checkf(LoadingWidget, TEXT("Loading Widget Not Set In %hs"), __FUNCTION__);

	LoadingWidget->HideBlurredLoadingPage();
}

void UUILoadingComponent::ShowClearLoadingPage()
{
	checkf(LoadingWidget, TEXT("Loading Widget Not Set In %hs"), __FUNCTION__);
	
}

void UUILoadingComponent::HideClearLoadingPage()
{
	checkf(LoadingWidget, TEXT("Loading Widget Not Set In %hs"), __FUNCTION__);
	
}
