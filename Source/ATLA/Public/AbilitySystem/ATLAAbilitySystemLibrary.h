// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/Asset/ATLACharacterInfo.h"

#include "ATLAAbilitySystemLibrary.generated.h"

struct FAbilityVisionLevel;
class UAbilitySystemComponent;
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
	UFUNCTION(BlueprintPure, Category = "ATLA|Ability System|Widget Controller", meta = ( WorldContext = "WorldContextObject" ))
	static UPlayerHUDWidgetController* GetPlayerHUDWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "ATLA|Ability System|Widget Controller", meta = ( WorldContext = "WorldContextObject" ))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ATLA|Ability System|Character")
	static void InitializeATLACharacterInfo(const UObject* WorldContextObject, ECharacterElement CharacterElement,
	                                        ECharacterType CharacterType, float Level, bool bIsPlayer, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintPure, Category = "ATLA|Ability|Vision")
	static FAbilityVisionLevel GetAbilityVisionLevel(UDataTable* DataTable, const FName RowName);

private:
	static void ApplyGameplayEffectToTarget(const TSubclassOf<UGameplayEffect>& Attribute, UAbilitySystemComponent* ASC, const AActor* AvatarActor, const int32 Level);
};
