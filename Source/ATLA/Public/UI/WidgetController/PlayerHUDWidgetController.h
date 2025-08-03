// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "ATLAGlobalDelegates.h"
#include "Data/Asset/ATLAAbilityInfo.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "PlayerHUDWidgetController.generated.h"

enum class ECharacterElement : uint8;
class UATLAAbilitySystemComponent;
class UATLAUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Message = FText();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UATLAUserWidget> MessageWidget;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FAbilityInfo&, Info);

/**
 * ATLA Player HUD Widget Controller Class.
 */
UCLASS(BlueprintType, Blueprintable)
class ATLA_API UPlayerHUDWidgetController : public UATLAWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "ATLA|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Attributes")
	FOnAttributeChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Attributes")
	FOnAttributeChangedSignature OnMaxStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Player Info")
	FOnCharacterSelectedSignature OnCharacterSelected;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Player Info")
	FAbilityInfoSignature AbilityInfoDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UDataTable> CharacterInfoDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UATLAAbilityInfo> AbilityInfo;
	
	void OnInitializeStartupAbilitiesGiven(UATLAAbilitySystemComponent* ATLAASC);

	UFUNCTION()
	void CharacterSelected(const FSelectedCharacter SelectedCharacter);
};
