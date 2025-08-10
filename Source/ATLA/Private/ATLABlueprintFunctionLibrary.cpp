// Copyright Melon Studios.

#include "ATLABlueprintFunctionLibrary.h"
#include "Component/UICutsceneComponent.h"
#include "Component/UIPopUpComponent.h"
#include "Enum/ECharacterElement.h"
#include "Game/ATLAGameInstance.h"
#include "Game/ATLAGameState.h"
#include "GameFramework/HUD.h"
#include "Interface/UICutsceneInterface.h"
#include "Interface/UILoadingInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FATLACharacters.h"
#include "Interface/UIPopUpInterface.h"

UATLAGameInstance* UATLABlueprintFunctionLibrary::GetATLAGameInstance(const UObject* WorldContextObject)
{
	return Cast<UATLAGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

FATLACharacters UATLABlueprintFunctionLibrary::GetCharacterData(UDataTable* DataTable, const FName RowName)
{
	return *GetDataTableRowByName<FATLACharacters>(DataTable, RowName);
}

FString UATLABlueprintFunctionLibrary::GetCharacterElementString(const ECharacterElement CharacterElement)
{
	switch (CharacterElement)
	{
	case ECharacterElement::Air:
		return "Air";
	case ECharacterElement::Water:
		return "Water";
	case ECharacterElement::Earth:
		return "Earth";
	case ECharacterElement::Fire:
		return "Fire";
	case ECharacterElement::NonBender:
		return "NonBender";
	default:
		return "";
	}
}

UCharacterSelectMenuViewModel* UATLABlueprintFunctionLibrary::GetCharacterSelectMenuViewModel(const UObject* WorldContextObject)
{
	const AATLAGameState* GS = Cast<AATLAGameState>(UGameplayStatics::GetGameState(WorldContextObject));
	return GS->GetCharacterSelectMenuViewModel();
}

FString UATLABlueprintFunctionLibrary::GetGameInfoDetails()
{
	FString GameName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		GameName,
		GGameIni);

	FString GameVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		GameVersion,
		GGameIni);

	FString CompanyName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("CompanyName"),
		CompanyName,
		GGameIni);

	return CompanyName + "-" + GameName + "-v" + GameVersion;
}

#pragma region UI Pop Up Interface Functions
void UATLABlueprintFunctionLibrary::ShowPopUpUI(const UObject* WorldContextObject, EUIPopUpWidget PopUpWidget)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUIPopUpInterface* PopUpInterface = HUD->FindComponentByInterface<IUIPopUpInterface>();
	PopUpInterface->ShowPopUpWidget(PopUpWidget);
}

void UATLABlueprintFunctionLibrary::PopUpUIYes(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUIPopUpInterface* PopUpInterface = HUD->FindComponentByInterface<IUIPopUpInterface>();
	PopUpInterface->PopUpWidgetYes();
}

void UATLABlueprintFunctionLibrary::PopUpUINo(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUIPopUpInterface* PopUpInterface = HUD->FindComponentByInterface<IUIPopUpInterface>();
	PopUpInterface->PopUpWidgetNo();
}
#pragma endregion

#pragma region UI Cutscene Interface Functions
void UATLABlueprintFunctionLibrary::ShowCutsceneHorizontalBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = HUD->FindComponentByInterface<IUICutsceneInterface>();
	CutsceneInterface->ShowCutsceneHorizontalBars();
}

void UATLABlueprintFunctionLibrary::HideCutsceneHorizontalBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = HUD->FindComponentByInterface<IUICutsceneInterface>();
	CutsceneInterface->HideCutsceneHorizontalBars();
}

void UATLABlueprintFunctionLibrary::ShowCutsceneVerticalBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = HUD->FindComponentByInterface<IUICutsceneInterface>();
	CutsceneInterface->ShowCutsceneVerticalBars();
}

void UATLABlueprintFunctionLibrary::HideCutsceneVerticalBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = HUD->FindComponentByInterface<IUICutsceneInterface>();
	CutsceneInterface->HideCutsceneVerticalBars();
}

void UATLABlueprintFunctionLibrary::ShowBlurredLoadingPage(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUILoadingInterface* LoadingInterface = HUD->FindComponentByInterface<IUILoadingInterface>();
	LoadingInterface->ShowBlurredLoadingPage();
}

void UATLABlueprintFunctionLibrary::HideBlurredLoadingPage(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUILoadingInterface* LoadingInterface = HUD->FindComponentByInterface<IUILoadingInterface>();
	LoadingInterface->HideBlurredLoadingPage();
}

void UATLABlueprintFunctionLibrary::ShowClearLoadingPage(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUILoadingInterface* LoadingInterface = HUD->FindComponentByInterface<IUILoadingInterface>();
	LoadingInterface->ShowClearLoadingPage();
}

void UATLABlueprintFunctionLibrary::HideClearLoadingPage(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUILoadingInterface* LoadingInterface = HUD->FindComponentByInterface<IUILoadingInterface>();
	LoadingInterface->HideClearLoadingPage();
}
#pragma endregion
