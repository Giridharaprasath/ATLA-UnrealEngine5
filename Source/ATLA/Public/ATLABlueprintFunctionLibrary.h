// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"

#include "ATLABlueprintFunctionLibrary.generated.h"

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

	/** UI Pop Up Interface Functions **/
	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext="WorldContextObject" ))
	static void ShowPopUpUI(const UObject* WorldContextObject, EUIPopUpWidget PopUpWidget);

	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext="WorldContextObject" ))
	static void PopUpUIYes(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ATLA|UI", meta = ( WorldContext="WorldContextObject" ))
	static void PopUpUINo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "ATLA|Character Data")
	static FATLACharacters GetCharacterData(UDataTable* DataTable, const FName RowName);

	template <typename T>
	static T* GetDataTableRowByName(UDataTable* DataTable, const FName& RowName);

	UFUNCTION(BlueprintPure, Category = "ATLA")
	static FString GetGameInfoDetails();
};

template <typename T>
T* UATLABlueprintFunctionLibrary::GetDataTableRowByName(UDataTable* DataTable, const FName& RowName)
{
	return DataTable->FindRow<T>(RowName, TEXT(""));
}
