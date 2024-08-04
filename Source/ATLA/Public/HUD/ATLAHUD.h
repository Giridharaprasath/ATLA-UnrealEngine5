// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "ATLAHUD.generated.h"

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

private:
	
	UPROPERTY()
	TObjectPtr<UATLAUserWidget> PlayerHUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UATLAUserWidget> PlayerHUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UPlayerHUDWidgetController> PlayerHUDWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUDWidgetController> PlayerHUDWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
