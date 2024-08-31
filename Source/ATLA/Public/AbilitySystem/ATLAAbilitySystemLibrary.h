// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ATLAAbilitySystemLibrary.generated.h"

class UPlayerHUDWidgetController;
class UAttributeMenuWidgetController;

/**
 *	ATLA Ability System Blueprint Library Class.
 */
UCLASS()
class ATLA_API UATLAAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ATLA|Ability System|Widget Controller",
		meta = ( WorldContext = "WorldContextObject" ))
	static UPlayerHUDWidgetController* GetPlayerHUDWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "ATLA|Ability System|Widget Controller",
		meta = ( WorldContext = "WorldContextObject" ))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
