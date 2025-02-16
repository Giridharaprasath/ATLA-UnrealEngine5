// Copyright Melon Studios.

#pragma once

#include "CoreMinimal.h"
#include "Data/Asset/ATLAAbilityInfo.h"
#include "UI/WidgetController/ATLAWidgetController.h"

#include "PlayerHUDWidgetController.generated.h"

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterNameChangedSignature, FText, NewCharacterName);
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
	FOnCharacterNameChangedSignature OnCharacterNameChanged;

	UPROPERTY(BlueprintAssignable, Category = "ATLA|Player Info")
	FAbilityInfoSignature AbilityInfoDelegate;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UDataTable> CharacterInfoDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ATLA|Widget Data")
	TObjectPtr<UATLAAbilityInfo> AbilityInfo;
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	void OnInitializeStartupAbilitiesGiven(UATLAAbilitySystemComponent* ATLAASC);
};

template <typename T>
T* UPlayerHUDWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
