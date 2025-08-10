// Copyright Melon Studios.

#include "GGRadarDeveloperSettings.h"

UGGRadarDeveloperSettings::UGGRadarDeveloperSettings()
{
	const UObject* Font = LoadObject<UObject>(nullptr,TEXT("/Engine/EngineFonts/RobotoTiny.RobotoTiny"));
	CommonFontInfo = FSlateFontInfo(Font, 15.f);

	RadarWidget = TSoftClassPtr<URadarWidget>(FSoftObjectPath(TEXT("/GGRadarSystem/WBP_RadarWidget.WBP_RadarWidget_C")));

	WorldDirectionWidget = TSoftClassPtr<UWorldDirectionWidget>(FSoftObjectPath(TEXT("/GGRadarSystem/WBP_RadarDirection.WBP_RadarDirection_C")));
	DirectionHorizontalAlignment = HAlign_Center;
	DirectionVerticalAlignment = VAlign_Bottom;
}

FName UGGRadarDeveloperSettings::GetCategoryName() const
{
	return TEXT("Plugins");
}

FText UGGRadarDeveloperSettings::GetSectionText() const
{
	return FText::FromString("GG Radar System");
}
