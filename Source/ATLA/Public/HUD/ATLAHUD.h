// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "ATLAHUD.generated.h"

class UATLAUserWidget;
class UPlayerHUDWidgetController;
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
	UPROPERTY()
	TObjectPtr<UATLAUserWidget> PlayerHUDWidget;

	UPlayerHUDWidgetController* GetPlayerHUDWidgetController(const FWidgetController& WidgetController);

	// TODO : CALL INIT PLAYER HUD TO CREATE PLAYER HUD, CALL THIS FUNCTION AFTER SELECTING CHARACTER 
	void InitPlayerHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UATLAUserWidget> PlayerHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUDWidgetController> PlayerHUDWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUDWidgetController> PlayerHUDWidgetControllerClass;
};
