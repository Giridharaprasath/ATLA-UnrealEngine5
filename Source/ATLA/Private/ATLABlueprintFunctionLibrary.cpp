// Copyright Melon Studios.

#include "ATLABlueprintFunctionLibrary.h"
#include "Component/UICutsceneComponent.h"
#include "Component/UIPopUpComponent.h"
#include "Enum/ECharacterElement.h"
#include "Game/ATLAGameInstance.h"
#include "Game/ATLAGameState.h"
#include "GameFramework/HUD.h"
#include "Interface/UICutsceneInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FATLACharacters.h"
#include "Interface/UIPopUpInterface.h"

UATLAGameInstance* UATLABlueprintFunctionLibrary::GetATLAGameInstance(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UATLAGameInstance* ATLAGameInstance = Cast<UATLAGameInstance>(GameInstance);
	return ATLAGameInstance;
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
	IUIPopUpInterface* PopUpInterface = Cast<IUIPopUpInterface>(HUD->FindComponentByClass<UUIPopUpComponent>());
	PopUpInterface->ShowPopUpWidget(PopUpWidget);
}

void UATLABlueprintFunctionLibrary::PopUpUIYes(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUIPopUpInterface* PopUpInterface = Cast<IUIPopUpInterface>(HUD->FindComponentByClass<UUIPopUpComponent>());
	PopUpInterface->PopUpWidgetYes();
}

void UATLABlueprintFunctionLibrary::PopUpUINo(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUIPopUpInterface* PopUpInterface = Cast<IUIPopUpInterface>(HUD->FindComponentByClass<UUIPopUpComponent>());
	PopUpInterface->PopUpWidgetNo();
}
#pragma endregion

#pragma region UI Cutscene Interface Functions
void UATLABlueprintFunctionLibrary::ShowCutsceneBlackBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = Cast<IUICutsceneInterface>(HUD->FindComponentByClass<UUICutsceneComponent>());
	CutsceneInterface->ShowCutsceneBlackBars();
}

void UATLABlueprintFunctionLibrary::HideCutsceneBlackBars(const UObject* WorldContextObject)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	const AHUD* HUD = PC->GetHUD();
	IUICutsceneInterface* CutsceneInterface = Cast<IUICutsceneInterface>(HUD->FindComponentByClass<UUICutsceneComponent>());
	CutsceneInterface->HideCutsceneBlackBars();
}
#pragma endregion
