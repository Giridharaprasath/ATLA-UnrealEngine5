// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RadarComponent.generated.h"

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

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Radar|Boolean")
	bool bIsVisible;
	UPROPERTY(BlueprintReadOnly, Category = "Radar|Configurations")
	TArray<FWorldDirection> WorldDirections;

private:
	void AddWorldDirectionsToWidget();
	
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraReference;
	UPROPERTY()
	TObjectPtr<AActor> PlayerReference;
	UPROPERTY()
	TObjectPtr<URadarWidget> RadarWidget;
	UPROPERTY()
	TSubclassOf<URadarWidget> RadarWidgetClass;
};
