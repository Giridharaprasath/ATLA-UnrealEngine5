// Copyright Melon Studios.

#include "ATLABlueprintFunctionLibrary.h"

FATLACharacters UATLABlueprintFunctionLibrary::GetCharacterData(UDataTable* DataTable, const FName RowName)
{
	return *GetDataTableRowByName<FATLACharacters>(DataTable, RowName);
}
