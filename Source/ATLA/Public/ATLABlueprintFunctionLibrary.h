// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"

#include "ATLABlueprintFunctionLibrary.generated.h"

class UCharacterSelectMenuViewModel;
enum class ECharacterElement : uint8;
enum class EUIPopUpWidget : uint8;
class UATLAGameInstance;
struct FATLACharacters;

/**
 *	ATLA Blueprint Function Library Class.
 */
UCLASS()
class ATLA_API UATLABlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ATLA", meta = ( WorldContext="WorldContextObject" ))
	static UATLAGameInstance* GetATLAGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "ATLA|Character Data")
	static FATLACharacters GetCharacterData(UDataTable* DataTable, const FName RowName);

	template <typename T>
	static T* GetDataTableRowByName(UDataTable* DataTable, const FName& RowName);

	template <typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	UFUNCTION(BlueprintPure, Category = "ATLA|Character Element")
	static FString GetCharacterElementString(const ECharacterElement CharacterElement);

#pragma region View Model Functions
	UFUNCTION(BlueprintPure, Category = "ATLA|Character|Selection", meta = ( WorldContext = "WorldContextObject" ))
	static UCharacterSelectMenuViewModel* GetCharacterSelectMenuViewModel(const UObject* WorldContextObject);
#pragma endregion

	UFUNCTION(BlueprintPure, Category = "ATLA")
	static FString GetGameInfoDetails();

#pragma region UI Pop Up Interface Functions
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext = "WorldContextObject" ))
	static void ShowPopUpUI(const UObject* WorldContextObject, EUIPopUpWidget PopUpWidget);

	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext = "WorldContextObject" ))
	static void PopUpUIYes(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext = "WorldContextObject" ))
	static void PopUpUINo(const UObject* WorldContextObject);
#pragma endregion

#pragma region UI Cutscene Interface Functions
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext = "WorldContextObject" ))
	static void ShowCutsceneBlackBars(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext = "WorldContextObject" ))
	static void HideCutsceneBlackBars(const UObject* WorldContextObject);
#pragma endregion
};

template <typename T>
T* UATLABlueprintFunctionLibrary::GetDataTableRowByName(UDataTable* DataTable, const FName& RowName)
{
	return DataTable->FindRow<T>(RowName, TEXT(""));
}

template <typename T>
T* UATLABlueprintFunctionLibrary::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
