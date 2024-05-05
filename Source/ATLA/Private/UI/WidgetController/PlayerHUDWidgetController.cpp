// Copyright Melon Studios.

#include "UI/WidgetController/PlayerHUDWidgetController.h"

#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"

void UPlayerHUDWidgetController::BroadcastInitialValues()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ATLAAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxStaminaChanged.Broadcast(ATLAAttributeSet->GetMaxStamina());
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
				const FString Msg = FString::Printf(TEXT("GE Tag : %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, Msg);

				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTagExact(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
