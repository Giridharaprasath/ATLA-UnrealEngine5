// Copyright Melon Studios.

#include "Character/ATLACharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ATLAAbilitySystemComponent.h"

AATLACharacterBase::AATLACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AATLACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AATLACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AATLACharacterBase::InitAbilityActorInfo()
{
}

void AATLACharacterBase::InitializeDefaultAttributes() const
{
}

void AATLACharacterBase::AddCharacterAbilities()
{
	// UATLAAbilitySystemComponent* ATLAASC = CastChecked<UATLAAbilitySystemComponent>(AbilitySystemComponent);
	// if (!HasAuthority()) return;
	//
	// ATLAASC->AddCharacterAbilities(StartupAbilities);
}
