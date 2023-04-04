// Developed By Melon Studios.

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

	// Get Game Name
	UFUNCTION(BlueprintPure, Category = "ATLA|HUD|Debug")
	static FString GetGameName();

	// Get Game Version
	UFUNCTION(BlueprintPure, Category = "ATLA||HUD|Debug")
	static FString GetGameVersion();

	// Get Company Name
	UFUNCTION(BlueprintPure, Category = "ATLA|HUD|Debug")
	static FString GetCompanyName();
};