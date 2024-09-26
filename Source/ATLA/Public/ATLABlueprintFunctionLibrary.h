// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLA/ATLA.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"

#include "ATLABlueprintFunctionLibrary.generated.h"

/**
 *	ATLA Blueprint Function Library Class.
 */
UCLASS()
class ATLA_API UATLABlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ATLA|Character Data")
	static FATLACharacters GetCharacterData(UDataTable* DataTable, const FName RowName);
	
	template <typename T>
	static T* GetDataTableRowByName(UDataTable* DataTable, const FName& RowName);
};

template <typename T>
T* UATLABlueprintFunctionLibrary::GetDataTableRowByName(UDataTable* DataTable, const FName& RowName)
{
	return DataTable->FindRow<T>(RowName, TEXT(""));
}
