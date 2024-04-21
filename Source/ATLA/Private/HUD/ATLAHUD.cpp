// Copyright Melon Studios.

#include "HUD/ATLAHUD.h"
#include "UI/Widget/ATLAUserWidget.h"

void AATLAHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	UserWidget->AddToViewport();
}
