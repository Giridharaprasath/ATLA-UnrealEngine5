// Copyright Melon Studios.

#include "WorldDirectionWidget.h"
#include "FWorldDirection.h"
#include "GGRadarDeveloperSettings.h"
#include "Components/TextBlock.h"

void UWorldDirectionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	const UGGRadarDeveloperSettings* RadarSettings = GetDefault<UGGRadarDeveloperSettings>();
	
	const FText WorldDirection = WorldDirectionInfo.DirectionName;
	DirectionText->SetText(WorldDirection.ToUpper());
	
	const FSlateFontInfo FontInfo = RadarSettings->CommonFontInfo;
	DirectionText->SetFont(FontInfo);
}
