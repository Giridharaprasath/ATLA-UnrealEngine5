// Copyright Melon Studios.

#include "RadarComponent.h"
#include "FRotationsToTranslation.h"
#include "FWorldDirection.h"
#include "GGRadarDeveloperSettings.h"
#include "RadarWidget.h"
#include "WorldDirectionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

URadarComponent::URadarComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsVisible = true;
	bCanChangeVisibility = true;

	const UGGRadarDeveloperSettings* RadarSettings = GetDefault<UGGRadarDeveloperSettings>();

	WorldDirections.Emplace(FText::FromString("N"), 0);
	WorldDirections.Emplace(FText::FromString("E"), 90);
	WorldDirections.Emplace(FText::FromString("S"), 180);
	WorldDirections.Emplace(FText::FromString("W"), 270);

	if (RadarSettings->bUse8Directions)
	{
		WorldDirections.Emplace(FText::FromString("NE"), 45);
		WorldDirections.Emplace(FText::FromString("SE"), 135);
		WorldDirections.Emplace(FText::FromString("SW"), 225);
		WorldDirections.Emplace(FText::FromString("NW"), 315);
	}

	RadarWidgetClass = RadarSettings->RadarWidget.LoadSynchronous();

	MaxWidgetTranslation = RadarSettings->MaxWidgetTranslation;

	OnPlayerTurnedDelegate.AddDynamic(this, &ThisClass::OnPlayerTurned);
}

void URadarComponent::InitializeRadar(UCameraComponent* Camera, AActor* Player)
{
	CameraReference = Camera;
	PlayerReference = Player;

	checkf(RadarWidgetClass, TEXT("Radar Widget Class Not Set In "), __FUNCTION__);

	RadarWidget = CreateWidget<URadarWidget>(GetWorld(), RadarWidgetClass);
	AddWorldDirectionsToWidget();

	RadarWidget->AddToViewport(0);

	OnPlayerTurnedDelegate.Broadcast();
}

void URadarComponent::ToggleRadarVisibility(const bool bCanAnimate)
{
	SetRadarVisibility(!bIsVisible, bCanAnimate);
}

void URadarComponent::OnPlayerTurned_Implementation()
{
	if (!bIsVisible) return;

	UpdateDirectionWidgets();
}

void URadarComponent::SetRadarVisibility(const bool bShowRadar, const bool bCanShowAnim)
{
	if (bShowRadar != bIsVisible && bCanChangeVisibility)
	{
		bCanChangeVisibility = false;
		bIsVisible = bShowRadar;

		if (bCanShowAnim)
		{
			if (bIsVisible)
			{
				RadarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				RadarWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			bCanChangeVisibility = true;
		}
		else
		{
			if (bIsVisible)
			{
				RadarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				RadarWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			bCanChangeVisibility = true;
		}
	}
}

void URadarComponent::AddWorldDirectionsToWidget()
{
	for (FWorldDirection Direction : WorldDirections)
	{
		RadarWidget->AddWorldDirection(Direction);
	}
}

void URadarComponent::UpdateDirectionWidgets()
{
	const TArray<UWorldDirectionWidget*> DirectionWidgets = RadarWidget->WorldDirectionWidgets;

	for (int i = 0; i < DirectionWidgets.Num(); i++)
	{
		const float Yaw = WorldDirections[i].WorldRotation;

		const FRotator RotationA = CameraReference->GetComponentRotation();
		const FRotator RotationB = FRotator(0.f, Yaw, 0.f);

		const FRotationsToTranslation CurrentRotationsToTranslation = RotationsToTranslation(RotationA, RotationB);

		if (CurrentRotationsToTranslation.bIsInRadarSight)
		{
			DirectionWidgets[i]->SetRenderTranslation(CurrentRotationsToTranslation.Translation);
			if (!DirectionWidgets[i]->IsVisible())
			{
				DirectionWidgets[i]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}
		else
		{
			if (DirectionWidgets[i]->IsVisible())
			{
				DirectionWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

FRotationsToTranslation URadarComponent::RotationsToTranslation(const FRotator& RotationA, const FRotator& RotationB) const
{
	const float YawB = RotationToCircleDegrees(RotationA.Yaw);
	const float YawA = RotationToCircleDegrees(RotationB.Yaw);

	float ClockwiseDelta = GetDeltaClockwise(YawA, YawB, true);
	float AntiClockwiseDelta = GetDeltaClockwise(YawA, YawB, false);

	if (ClockwiseDelta > AntiClockwiseDelta)
	{
		AntiClockwiseDelta /= CameraReference->FieldOfView;
		if (AntiClockwiseDelta <= 1)
		{
			const float OutValue = FMath::Lerp(0.f, MaxWidgetTranslation, AntiClockwiseDelta) * -1;
			return FRotationsToTranslation(OutValue, false, true);
		}
		else
		{
			return FRotationsToTranslation();
		}
	}
	else
	{
		ClockwiseDelta /= CameraReference->FieldOfView;
		if (ClockwiseDelta <= 1)
		{
			const float OutValue = FMath::Lerp(0.f, MaxWidgetTranslation, ClockwiseDelta);
			return FRotationsToTranslation(OutValue, true, true);
		}
		else
		{
			return FRotationsToTranslation(0.f, true, false);
		}
	}
}

float URadarComponent::RotationToCircleDegrees(const float InValue) const
{
	if (InValue > 0) return InValue;
	return FMath::Fmod(InValue + 360.f, 360.f);
}

float URadarComponent::GetDeltaClockwise(const float A, const float B, const bool bIsClockwise) const
{
	const float ModA = FMath::Fmod(A, 360.f);
	const float ModB = FMath::Fmod(B, 360.f);

	if (bIsClockwise)
	{
		if (ModA > ModB)
		{
			return 360.f - (ModA - ModB);
		}
		if (ModA < ModB)
		{
			return ModB - ModA;
		}
		return 0;
	}
	else
	{
		if (ModA > ModB)
		{
			return ModA - ModB;
		}
		if (ModA < ModB)
		{
			return 360.f - (ModB - ModA);
		}
		return 0;
	}
}
