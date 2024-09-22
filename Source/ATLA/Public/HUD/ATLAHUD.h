// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "ATLAHUD.generated.h"

class UATLACommonActivatableWidget;
class UATLACommonUserWidget;
class UATLAUserWidget;
class UPlayerHUDWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * ATLA HUD Base Class.
 */
UCLASS()
class ATLA_API AATLAHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPlayerHUDWidgetController* GetPlayerHUDWidgetController(const FWidgetController& WidgetController);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetController& WidgetController);

	// TODO : CALL INIT PLAYER HUD TO CREATE PLAYER HUD, CALL THIS FUNCTION AFTER SELECTING CHARACTER 
	void InitPlayerHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATLA|HUD")
	void OpenPauseMenu();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "ATLA|HUD")
	void CreatePlayerUIBaseWidget();
	
	UFUNCTION(BlueprintPure, Category = "ATLA|HUD|Debug")
	FString GetGameName();
	UFUNCTION(BlueprintPure, Category = "ATLA|HUD|Debug")
	FString GetGameVersion();
	UFUNCTION(BlueprintPure, Category = "ATLA|HUD|Debug")
	FString GetCompanyName();

private:
	
	UPROPERTY()
	TObjectPtr<UATLAUserWidget> PlayerHUDWidget;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UATLAUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UPlayerHUDWidgetController> PlayerHUDWidgetController;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UPlayerHUDWidgetController> PlayerHUDWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UATLACommonUserWidget> PlayerUIWidgetBase;
	UPROPERTY(EditAnywhere, Category = "ATLA|HUD")
	TSubclassOf<UATLACommonUserWidget> PlayerUIWidgetBaseClass;

	UPROPERTY(EditAnywhere, Category = "ATLA|HUD|Pause Menu")
	TSubclassOf<UATLACommonActivatableWidget> PauseMenuWidget;
	
};
