// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "GGRadarDeveloperSettings.generated.h"

class URadarWidget;
class UWorldDirectionWidget;

/**
 *	GG Radar System Developer Settings Class.
 */
UCLASS(Config = "GGRadarSettings", DefaultConfig, meta = (DisplayName = "GG Radar Settings"), MinimalAPI)
class UGGRadarDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UGGRadarDeveloperSettings();
	virtual FName GetCategoryName() const override;
	virtual FText GetSectionText() const override;

	UPROPERTY(Config, EditDefaultsOnly, Category = "UI")
	FSlateFontInfo CommonFontInfo;

	UPROPERTY(Config, EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<URadarWidget> RadarWidget;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Direction Widget")
	TSoftClassPtr<UWorldDirectionWidget> WorldDirectionWidget;
	UPROPERTY(Config, EditDefaultsOnly, Category = "Direction Widget")
	TEnumAsByte<EHorizontalAlignment> DirectionHorizontalAlignment;
	UPROPERTY(Config, EditDefaultsOnly, Category = "Direction Widget")
	TEnumAsByte<EVerticalAlignment> DirectionVerticalAlignment;
};
