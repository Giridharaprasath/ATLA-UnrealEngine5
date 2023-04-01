// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ATLAHUD.generated.h"


/**
 * 
 */
UCLASS()
class ATLAPROJECT_API AATLAHUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void CreatePlayerHUD();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void SetPlayerHealthBar(float HealthPercentage);
};