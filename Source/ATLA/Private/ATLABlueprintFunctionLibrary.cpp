// Copyright Melon Studios.

#include "ATLABlueprintFunctionLibrary.h"
#include "Component/UIPopUpComponent.h"
#include "Game/ATLAGameInstance.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FATLACharacters.h"
#include "Interface/UIPopUpInterface.h"

UATLAGameInstance* UATLABlueprintFunctionLibrary::GetATLAGameInstance(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UATLAGameInstance* ATLAGameInstance = Cast<UATLAGameInstance>(GameInstance);
	return ATLAGameInstance;
}

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

FATLACharacters UATLABlueprintFunctionLibrary::GetCharacterData(UDataTable* DataTable, const FName RowName)
{
	return *GetDataTableRowByName<FATLACharacters>(DataTable, RowName);
}
