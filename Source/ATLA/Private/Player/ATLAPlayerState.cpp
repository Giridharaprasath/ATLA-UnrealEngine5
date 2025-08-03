// Copyright Melon Studios.

#include "Player/ATLAPlayerState.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"
#include "AbilitySystem/ATLAAttributeSet.h"
#include "Enum/ECharacterElement.h"
#include "Net/UnrealNetwork.h"

AATLAPlayerState::AATLAPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UATLAAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UATLAAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);
}

void AATLAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AATLAPlayerState, Level);
	DOREPLIFETIME(AATLAPlayerState, SelectedCharacter);
}

UAbilitySystemComponent* AATLAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AATLAPlayerState::SetCharacterElement(const ECharacterElement InCharacterElement)
{
	SelectedCharacter.CharacterElement = InCharacterElement;
	SelectedCharacter.bIsSelected = true;
	OnCharacterSelected.Broadcast(SelectedCharacter);
}

void AATLAPlayerState::OnRep_Level(int32 OldLevel)
{
}

void AATLAPlayerState::OnRep_SelectedCharacter(FSelectedCharacter OldSelectedCharacter)
{
}
