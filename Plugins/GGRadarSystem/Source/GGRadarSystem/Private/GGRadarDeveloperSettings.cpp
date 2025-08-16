// Copyright Melon Studios.

#include "GGRadarDeveloperSettings.h"
#include "FWorldDirection.h"

UGGRadarDeveloperSettings::UGGRadarDeveloperSettings()
{
	const UObject* Font = LoadObject<UObject>(nullptr,TEXT("/Engine/EngineFonts/RobotoTiny.RobotoTiny"));
	CommonFontInfo = FSlateFontInfo(Font, 15.f);

	RadarWidget = TSoftClassPtr<URadarWidget>(FSoftObjectPath(TEXT("/GGRadarSystem/WBP_RadarWidget.WBP_RadarWidget_C")));

	WorldDirectionWidget = TSoftClassPtr<UWorldDirectionWidget>(FSoftObjectPath(TEXT("/GGRadarSystem/WBP_RadarDirection.WBP_RadarDirection_C")));
	bUse8Directions = false;
	CreateWidgetDirections();
	DirectionHorizontalAlignment = HAlign_Center;
	DirectionVerticalAlignment = VAlign_Bottom;
	MaxWidgetTranslation = 320.f;
}

FName UGGRadarDeveloperSettings::GetCategoryName() const
{
	return TEXT("Plugins");
}

FText UGGRadarDeveloperSettings::GetSectionText() const
{
	return FText::FromString("GG Radar System");
}

void UGGRadarDeveloperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (bUse8Directions && WorldDirections.Num() != 8)
	{
		CreateWidgetDirections();
	}
	if (!bUse8Directions && WorldDirections.Num() != 4)
	{
		CreateWidgetDirections();
	}
}

void UGGRadarDeveloperSettings::CreateWidgetDirections()
{
	WorldDirections.Empty();
	WorldDirections.Emplace(FText::FromString("N"), 0);
	WorldDirections.Emplace(FText::FromString("E"), 90);
	WorldDirections.Emplace(FText::FromString("S"), 180);
	WorldDirections.Emplace(FText::FromString("W"), 270);

	if (bUse8Directions)
	{
		WorldDirections.Emplace(FText::FromString("NE"), 45);
		WorldDirections.Emplace(FText::FromString("SE"), 135);
		WorldDirections.Emplace(FText::FromString("SW"), 225);
		WorldDirections.Emplace(FText::FromString("NW"), 315);
	}
}
