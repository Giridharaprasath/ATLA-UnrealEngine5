// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ATLAPlayerHUDUI.generated.h"

/**
 * 
 */
UCLASS()
class ATLAPROJECT_API UATLAPlayerHUDUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|UI")
	void SetPlayerHealthBar(float HealthPercentage);
};