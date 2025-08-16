// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RadarComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProcessSignature);

struct FRotationsToTranslation;
struct FWorldDirection;
class URadarWidget;
class UCameraComponent;

/*
 *	Radar System Component Class.
 */
UCLASS(Blueprintable, ClassGroup = ( Radar ), meta = ( BlueprintSpawnableComponent ))
class GGRADARSYSTEM_API URadarComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URadarComponent();

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void InitializeRadar(UCameraComponent* Camera, AActor* Player);
	UFUNCTION(BlueprintCallable, Category = "Radar")
	void ToggleRadarVisibility(const bool bCanAnimate);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Radar")
	void OnPlayerTurned();

	UPROPERTY(BlueprintAssignable, Category = "Radar")
	FOnProcessSignature OnPlayerTurnedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Radar")
	FOnProcessSignature OnPlayerMovedDelegate;

private:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraReference;
	UPROPERTY()
	TObjectPtr<AActor> PlayerReference;
	UPROPERTY()
	TObjectPtr<URadarWidget> RadarWidget;
	UPROPERTY()
	TSubclassOf<URadarWidget> RadarWidgetClass;
	
	UPROPERTY(VisibleAnywhere, Category = "Radar|Boolean")
	bool bIsVisible;
	UPROPERTY(VisibleAnywhere, Category = "Radar|Boolean")
	bool bCanChangeVisibility;

	UPROPERTY(VisibleAnywhere, Category = "Radar|Configurations")
	TArray<FWorldDirection> WorldDirections;
	UPROPERTY(VisibleAnywhere, Category = "Radar|Configurations")
	float MaxWidgetTranslation;

	void SetRadarVisibility(const bool bShowRadar, const bool bCanShowAnim);

	void AddWorldDirectionsToWidget();
	void UpdateDirectionWidgets();

#pragma region Calculations
	FRotationsToTranslation RotationsToTranslation(const FRotator& RotationA, const FRotator& RotationB) const;
	float RotationToCircleDegrees(const float InValue) const;
	float GetDeltaClockwise(const float A, const float B, const bool bIsClockwise) const;
#pragma endregion
};
