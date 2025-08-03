// Copyright Melon Studios.

#include "UI/WidgetController/PlayerHUDWidgetController.h"
#include "ATLABlueprintFunctionLibrary.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "Player/ATLAPlayerState.h"

void UPlayerHUDWidgetController::BroadcastInitialValues()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ATLAAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxStaminaChanged.Broadcast(ATLAAttributeSet->GetMaxStamina());

	const AATLAPlayerState* ATLAPlayerState = CastChecked<AATLAPlayerState>(PlayerState);
	CharacterSelected(ATLAPlayerState->GetSelectedCharacter());
}

void UPlayerHUDWidgetController::BindCallbacksToDependencies()
{
	Cast<AATLAPlayerState>(PlayerState)->OnCharacterSelected.AddDynamic(this, &ThisClass::CharacterSelected);

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

	if (UATLAAbilitySystemComponent* ATLAASC = Cast<UATLAAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (ATLAASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilitiesGiven(ATLAASC);
		}
		else
		{
			ATLAASC->AbilitiesGiven.AddUObject(this, &ThisClass::OnInitializeStartupAbilitiesGiven);
		}

		ATLAASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = UATLABlueprintFunctionLibrary::GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UPlayerHUDWidgetController::OnInitializeStartupAbilitiesGiven(UATLAAbilitySystemComponent* ATLAASC)
{
	if (!ATLAASC->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, ATLAASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(ATLAASC->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = ATLAASC->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	ATLAASC->ForEachAbility(BroadcastDelegate);
}

void UPlayerHUDWidgetController::CharacterSelected(const FSelectedCharacter SelectedCharacter)
{	
	OnCharacterSelected.Broadcast(SelectedCharacter);
}
