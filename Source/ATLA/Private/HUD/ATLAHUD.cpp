// Copyright Melon Studios.

#include "HUD/ATLAHUD.h"
#include "UI/Widget/ATLACommonActivatableWidget.h"
#include "UI/Widget/ATLAUserWidget.h"
#include "UI/Widget/ATLACommonUserWidget.h"
#include "UI/WidgetController/PlayerHUDWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UPlayerHUDWidgetController* AATLAHUD::GetPlayerHUDWidgetController(const FWidgetController& WidgetController)
{
	if (PlayerHUDWidgetController == nullptr)
	{
		PlayerHUDWidgetController = NewObject<UPlayerHUDWidgetController>(this, PlayerHUDWidgetControllerClass);
		PlayerHUDWidgetController->SetWidgetController(WidgetController);
		PlayerHUDWidgetController->BindCallbacksToDependencies();
	}

	return PlayerHUDWidgetController;
}

UAttributeMenuWidgetController* AATLAHUD::GetAttributeMenuWidgetController(const FWidgetController& WidgetController)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetController(WidgetController);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
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

void AATLAHUD::OpenPauseMenu_Implementation()
{
	checkf(PauseMenuWidget, TEXT("Pause Menu Widget Not Set in BP_HUD_ATLA"));
	
	PlayerUIWidgetBase->PushToMenuUIStack(PauseMenuWidget);
}

void AATLAHUD::OpenCharacterSelectUIWidget_Implementation()
{
	checkf(CharacterSelectWidget, TEXT("Character Select Widget Not Set in BP_HUD_ATLA"));

	PlayerUIWidgetBase->PushToMenuUIStack(CharacterSelectWidget);
}

void AATLAHUD::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerUIBaseWidget();
	OpenCharacterSelectUIWidget();
}

void AATLAHUD::CreatePlayerUIBaseWidget_Implementation()
{
	checkf(PlayerUIWidgetBaseClass, TEXT("Player UI Widget Base Class Not Set in BP_HUD_ATLA"));

	UCommonUserWidget* CommonUserWidget = CreateWidget<UCommonUserWidget>(GetWorld(), PlayerUIWidgetBaseClass);
	PlayerUIWidgetBase = Cast<UATLACommonUserWidget>(CommonUserWidget);

	CommonUserWidget->AddToViewport();
}

FString AATLAHUD::GetGameName()
{
	FString GameName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		GameName,
		GGameIni);
	return GameName;
}

FString AATLAHUD::GetGameVersion()
{
	FString GameVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		GameVersion,
		GGameIni);
	return GameVersion;
}

FString AATLAHUD::GetCompanyName()
{
	FString CompanyName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("CompanyName"),
		CompanyName,
		GGameIni);
	return CompanyName;
}
