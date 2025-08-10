// Copyright Melon Studios.

#include "RadarWidget.h"
#include "FWorldDirection.h"
#include "GGRadarDeveloperSettings.h"
#include "WorldDirectionWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void URadarWidget::PlayRadarBlendAnim_Implementation(const bool bShowRadar)
{
	const EUMGSequencePlayMode::Type PlayAnimType = bShowRadar ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse;
	PlayAnimation(RadarBlendAnim, 0, 1, PlayAnimType, 1.f, false);
}

void URadarWidget::AddWorldDirection(const FWorldDirection& WorldDirection)
{
	if (!WorldDirectionWidgetClass)
	{
		SetWidgetClass();
	}

	checkf(WorldDirectionWidgetClass, TEXT("World Direction Widget Class Not Set In "), __FUNCTION__);
	UWorldDirectionWidget* DirectionWidget = CreateWidget<UWorldDirectionWidget>(GetWorld(), WorldDirectionWidgetClass);

	DirectionWidget->WorldDirectionInfo = WorldDirection;
	WorldDirectionWidgets.Add(DirectionWidget);

	if (UOverlaySlot* WidgetOverlaySlot = RadarOverlay->AddChildToOverlay(DirectionWidget))
	{
		WidgetOverlaySlot->SetHorizontalAlignment(HorizontalAlignment);
		WidgetOverlaySlot->SetVerticalAlignment(VerticalAlignment);
	}
}

void URadarWidget::SetWidgetClass()
{
	const UGGRadarDeveloperSettings* RadarSettings = GetDefault<UGGRadarDeveloperSettings>();
	WorldDirectionWidgetClass = RadarSettings->WorldDirectionWidget.LoadSynchronous();
	HorizontalAlignment = RadarSettings->DirectionHorizontalAlignment;
	VerticalAlignment = RadarSettings->DirectionVerticalAlignment;
}
