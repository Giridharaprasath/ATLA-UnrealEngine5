// Copyright Melon Studios.

#include "Player/ATLAPlayerState.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "Net/UnrealNetwork.h"

AATLAPlayerState::AATLAPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UATLAAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UATLAAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AATLAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AATLAPlayerState, Level);
}

UAbilitySystemComponent* AATLAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AATLAPlayerState::OnRep_Level(int32 OldLevel)
{
}
