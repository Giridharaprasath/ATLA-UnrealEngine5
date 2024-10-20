// Copyright Melon Studios.

#include "UI/WidgetController/PlayerHUDWidgetController.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "ATLA/ATLA.h"
#include "Player/ATLAPlayerState.h"

void UPlayerHUDWidgetController::BroadcastInitialValues()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ATLAAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxStaminaChanged.Broadcast(ATLAAttributeSet->GetMaxStamina());

	const AATLAPlayerState* ATLAPlayerState = CastChecked<AATLAPlayerState>(PlayerState);

	OnCharacterNameChanged.Broadcast(ATLAPlayerState->GetCharacterName());
}

void UPlayerHUDWidgetController::BindCallbacksToDependencies()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UATLAAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{			
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
