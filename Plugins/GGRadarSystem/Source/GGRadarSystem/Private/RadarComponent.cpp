// Copyright Melon Studios.

#include "RadarComponent.h"
#include "FWorldDirection.h"
#include "GGRadarDeveloperSettings.h"
#include "RadarWidget.h"
#include "Blueprint/UserWidget.h"

URadarComponent::URadarComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsVisible = true;

	WorldDirections.Emplace(FText::FromString("N"), 0);
	WorldDirections.Emplace(FText::FromString("E"), 90);
	WorldDirections.Emplace(FText::FromString("S"), 180);
	WorldDirections.Emplace(FText::FromString("W"), -90);

	const UGGRadarDeveloperSettings* RadarSettings = GetDefault<UGGRadarDeveloperSettings>();
	RadarWidgetClass = RadarSettings->RadarWidget.LoadSynchronous();
}

void URadarComponent::InitializeRadar(UCameraComponent* Camera, AActor* Player)
{
	CameraReference = Camera;
	PlayerReference = Player;

	checkf(RadarWidgetClass, TEXT("Radar Widget Class Not Set In "), __FUNCTION__);

	RadarWidget = CreateWidget<URadarWidget>(GetWorld(), RadarWidgetClass);
	AddWorldDirectionsToWidget();

	RadarWidget->AddToViewport(0);
}

void URadarComponent::AddWorldDirectionsToWidget()
{
	for (FWorldDirection Direction : WorldDirections)
	{
		RadarWidget->AddWorldDirection(Direction);
	}
}
