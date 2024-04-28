// Copyright Melon Studios.

#include "HUD/ATLAHUD.h"
#include "UI/Widget/ATLAUserWidget.h"
#include "UI/WidgetController/PlayerHUDWidgetController.h"

UPlayerHUDWidgetController* AATLAHUD::GetPlayerHUDWidgetController(const FWidgetController& WidgetController)
{
	if (PlayerHUDWidgetController == nullptr)
	{
		PlayerHUDWidgetController = NewObject<UPlayerHUDWidgetController>(this, PlayerHUDWidgetControllerClass);
		PlayerHUDWidgetController->SetWidgetController(WidgetController);
		PlayerHUDWidgetController->BindCallbacksToDependencies();
 
		return PlayerHUDWidgetController;
	}

	return PlayerHUDWidgetController;
}

void AATLAHUD::InitPlayerHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(PlayerHUDWidgetClass, TEXT("Player HUD Widget Class Not Set in BP_HUD_ATLA"));
	checkf(PlayerHUDWidgetControllerClass, TEXT("Player HUD Widget Controller Class Not Set in BP_HUD_ATLA"));

	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	PlayerHUDWidget = Cast<UATLAUserWidget>(UserWidget);

	const FWidgetController WidgetController(PC, PS, ASC, AS);
	UPlayerHUDWidgetController* PlayerWidgetController = GetPlayerHUDWidgetController(WidgetController);

	PlayerHUDWidget->SetWidgetController(PlayerWidgetController);
	PlayerWidgetController->BroadcastInitialValues();

	UserWidget->AddToViewport();
}
