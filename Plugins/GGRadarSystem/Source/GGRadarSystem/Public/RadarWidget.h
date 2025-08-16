// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RadarWidget.generated.h"

class UWorldDirectionWidget;
struct FWorldDirection;
class UImage;
class UOverlay;

/**
 *	Radar System Widget Class.
 */
UCLASS()
class GGRADARSYSTEM_API URadarWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Radar")
	void PlayRadarBlendAnim(const bool bShowRadar);
	
	UPROPERTY(BlueprintReadOnly, Category = "Radar", meta = ( BindWidget ))
	TObjectPtr<UOverlay> RadarOverlay;
	UPROPERTY(BlueprintReadOnly, Category = "Radar", meta = ( BindWidget ))
	TObjectPtr<UImage> RadarImage;

	UPROPERTY(BlueprintReadOnly, Category = "Radar|UI")
	TArray<UWorldDirectionWidget*> WorldDirectionWidgets;
	void AddWorldDirection(const FWorldDirection& WorldDirection);
	
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Radar", meta = ( BindWidgetAnim ))
	TObjectPtr<UWidgetAnimation> RadarBlendAnim;

private:
	UPROPERTY()
	TSubclassOf<UWorldDirectionWidget> WorldDirectionWidgetClass;
	
	EHorizontalAlignment HorizontalAlignment;
	EVerticalAlignment VerticalAlignment;

	void SetWidgetClass();
};
