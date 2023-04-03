// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ATLAHUD.generated.h"


/**
 * ATLA HUD Class.
 */
UCLASS()
class ATLAPROJECT_API AATLAHUD : public AHUD
{
	GENERATED_BODY()

public:

	// Create Current Player UI
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void CreatePlayerHUD();

	// Create Team Member Infos UI
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void CreateTeamHUD();

	// Set Current Player Health Bar
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void SetPlayerHealthBar(float HealthPercentage);

	// Set Current Player Character Name
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ATLA|HUD")
	void SetCharacterName(const FText& Name);
};