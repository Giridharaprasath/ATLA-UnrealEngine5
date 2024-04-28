// Copyright Melon Studios.

#include "UI/WidgetController/PlayerHUDWidgetController.h"
#include "AbilitySystem/ATLAAttributeSet.h"

void UPlayerHUDWidgetController::BroadcastInitialValues()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ATLAAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ATLAAttributeSet->GetMaxHealth());
}

void UPlayerHUDWidgetController::BindCallbacksToDependencies()
{
	const UATLAAttributeSet* ATLAAttributeSet = CastChecked<UATLAAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ATLAAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);
}

void UPlayerHUDWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UPlayerHUDWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
