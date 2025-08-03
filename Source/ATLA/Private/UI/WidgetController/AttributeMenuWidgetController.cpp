// Copyright Melon Studios.

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "Data/Asset/ATLAAttributeSetInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UATLAAttributeSet* AS = CastChecked<UATLAAttributeSet>(AttributeSet);

	check(ATLAAttributeSetInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UATLAAttributeSet* AS = CastChecked<UATLAAttributeSet>(AttributeSet);

	check(ATLAAttributeSetInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAttributeSetInfo Info = ATLAAttributeSetInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
