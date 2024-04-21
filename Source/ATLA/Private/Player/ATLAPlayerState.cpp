// Copyright Melon Studios.

#include "Player/ATLAPlayerState.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"

AATLAPlayerState::AATLAPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UATLAAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UATLAAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AATLAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
